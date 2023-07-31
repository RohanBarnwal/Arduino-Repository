import cv2
import dlib
import numpy as np
import imutils
from scipy.spatial import distance as dist
import time
import serial

# Load the face and eye detector from dlib
face_detector = dlib.get_frontal_face_detector()
landmark_predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

# Constants for EAR and blink detection
EAR_THRESHOLD = 0.3
MAR_THRESHOLD = 0.4
CONSECUTIVE_FRAMES_BLINK_THRESHOLD = 3
CONSECUTIVE_FRAMES_YAWN_START_THRESHOLD = 20
CONSECUTIVE_FRAMES_YAWN_STOP_THRESHOLD = 10

# Initialize serial communication with Arduino
arduino_port = "COM3"  # Replace with the appropriate port for your Arduino
arduino_baudrate = 9600
ser = serial.Serial(arduino_port, arduino_baudrate, timeout=1)

def eye_aspect_ratio(eye):
    A = dist.euclidean(eye[1], eye[5])
    B = dist.euclidean(eye[2], eye[4])
    C = dist.euclidean(eye[0], eye[3])
    ear = (A + B) / (2.0 * C)
    return ear

def get_landmarks(im):
    rects = face_detector(im, 1)
    if len(rects) > 1 or len(rects) == 0:
        return "error"
    return np.matrix([[p.x, p.y] for p in landmark_predictor(im, rects[0]).parts()])

def annotate_landmarks(im, landmarks):
    im = im.copy()
    for idx, point in enumerate(landmarks):
        pos = (point[0, 0], point[0, 1])
        cv2.putText(im, str(idx), pos,
                    fontFace=cv2.FONT_HERSHEY_SCRIPT_SIMPLEX,
                    fontScale=0.4,
                    color=(1, 2, 255))
        cv2.circle(im, pos, 3, color=(0, 2, 2))
    return im

def top_lip(landmarks):
    top_lip_pts = []
    for i in range(50, 53):
        top_lip_pts.append(landmarks[i])
    for i in range(61, 64):
        top_lip_pts.append(landmarks[i])
    top_lip_all_pts = np.squeeze(np.asarray(top_lip_pts))
    top_lip_mean = np.mean(top_lip_pts, axis=0)
    return int(top_lip_mean[:, 1])

def bottom_lip(landmarks):
    bottom_lip_pts = []
    for i in range(65, 68):
        bottom_lip_pts.append(landmarks[i])
    for i in range(56, 59):
        bottom_lip_pts.append(landmarks[i])
    bottom_lip_all_pts = np.squeeze(np.asarray(bottom_lip_pts))
    bottom_lip_mean = np.mean(bottom_lip_pts, axis=0)
    return int(bottom_lip_mean[:, 1])

def mouth_open(image):
    landmarks = get_landmarks(image)
    
    if landmarks == "error":
        return image, 0
    
    image_with_landmarks = annotate_landmarks(image, landmarks)
    top_lip_center = top_lip(landmarks)
    bottom_lip_center = bottom_lip(landmarks)
    lip_distance = abs(top_lip_center - bottom_lip_center)
    return image_with_landmarks, lip_distance

# Set the desired frame width and height for increased FPS
FRAME_WIDTH = 640
FRAME_HEIGHT = 480

# Start the video stream
cap = cv2.VideoCapture(0)

# Set the frame width and height for the video stream
cap.set(cv2.CAP_PROP_FRAME_WIDTH, FRAME_WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT)

# Initialize variables for blink and yawn detection
blink_counter = 0
total_blinks = 0
yawns = 0
yawn_status = False
time_eye_closed = None
time_yawn_detected = None
prev_yawn_status = False  # Initialize the previous yawn status

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Resize the frame to a smaller width to speed up processing
    frame = imutils.resize(frame, width=FRAME_WIDTH)

    # Convert the frame to grayscale for blink detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the grayscale frame
    faces = face_detector(gray)

    for face in faces:
        # Get the facial landmarks for the face
        landmarks = landmark_predictor(gray, face)
        left_eye = []
        right_eye = []

        # Extract left and right eye landmarks
        for i in range(36, 42):  # Left eye landmarks (36-41)
            left_eye.append((landmarks.part(i).x, landmarks.part(i).y))
        for i in range(42, 48):  # Right eye landmarks (42-47)
            right_eye.append((landmarks.part(i).x, landmarks.part(i).y))

        # Calculate eye aspect ratio (EAR) for left and right eye
        left_ear = eye_aspect_ratio(left_eye)
        right_ear = eye_aspect_ratio(right_eye)

        # Average the EAR of both eyes
        ear = (left_ear + right_ear) / 2.0

        # Check for blink
        if ear < EAR_THRESHOLD:
            blink_counter += 1
            if time_eye_closed is None:
                time_eye_closed = time.time()  # Record the time when eyes are first closed
        else:
            if blink_counter >= CONSECUTIVE_FRAMES_BLINK_THRESHOLD:
                total_blinks += 1
                # Check if the eyes were closed for more than 1 second
                if time_eye_closed is not None and time.time() - time_eye_closed >= 1.0:
                    # Send "1" to Arduino when eyes are closed for 1 second or more
                    print("Sending 1 to Arduino - Eyes closed for 1 second or more")
                    ser.write(b'1')  # Sending the byte '1' to Arduino
                    ser.flush()  # Wait for the data to be sent
                time_eye_closed = None  # Reset the eye closure time when eyes are open

            blink_counter = 0

        # Draw the eyes on the frame
        for eye in [left_eye, right_eye]:
            for i in range(0, len(eye) - 1):
                cv2.line(frame, eye[i], eye[i + 1], (0, 255, 0), 1)

    # Calculate mouth aspect ratio (MAR) and check for yawn
    image_landmarks, lip_distance = mouth_open(frame)

    prev_yawn_status = yawn_status
    if lip_distance > 25:
        yawn_status = True
        if time_yawn_detected is None:
            time_yawn_detected = time.time()  # Record the time when a yawn is first detected
    else:
        yawn_status = False
        if time_yawn_detected is not None:
            # Send "2" to Arduino when a yawn is detected
            print("Sending 2 to Arduino - Yawn detected")
            ser.write(b'2')  # Sending the byte '2' to Arduino
            ser.flush()  # Wait for the data to be sent
            time_yawn_detected = None  # Reset the yawn detection time

    if prev_yawn_status and not yawn_status:
        yawns += 1

    # Display the frame with annotations
    cv2.putText(frame, f"Total blinks: {total_blinks}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    cv2.putText(frame, f"Total yawns: {yawns}", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
    cv2.imshow("Eye Blink and Yawn Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release the video stream and close the OpenCV windows
cap.release()
cv2.destroyAllWindows()
ser.close()  # Close the serial connection with Arduino

print(f"Total blinks detected: {total_blinks}")
print(f"Total yawns detected: {yawns}")
