import cv2
import dlib
import telebot
import threading
import serial

# Initialize the serial port for communication with the Arduino
arduino_port = 'COM3'  # Replace with the correct port for your Arduino
arduino_baudrate = 9600  # Replace with the baud rate of your Arduino

ser = serial.Serial(arduino_port, arduino_baudrate)


# Initialize the Telegram bot with your bot token
bot = telebot.TeleBot('6489899565:AAH0UgAnv8Di0uEX42ftzyCdzw3co--oUnI')


# Initialize the webcam
cap = cv2.VideoCapture(0)

# Initialize the face detector from dlib
detector = dlib.get_frontal_face_detector()

# Load the facial landmarks predictor model
predictor = dlib.shape_predictor('shape_predictor_68_face_landmarks.dat')

# Initialize a variable to keep track of the previous location
prev_location = None

# Variable to track whether a welcome message has been sent
welcome_sent = False

# Initialize variable A
A = 0

# Function to handle user replies
# Function to handle user replies
@bot.message_handler(func=lambda message: True)
def handle_user_reply(message):
    # Access the global variable A

    user_response = message.text.lower()  # Get the user's response in lowercase

    if user_response == "yes":
        # Send a confirmation message and turn off the lights
        bot.send_message('5084417621', "Turning off all the lights.")
        ser.write(b'D')
        # Add code here to turn off the lights

    elif user_response == "no":
        # Send a confirmation message
        
        bot.send_message('5084417621', "Lights will remain on.")
        
    elif user_response == "turn on light1":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning On Light 1.")
        ser.write(b'P')
    
    elif user_response == "turn on light2":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning On Light 2.")
        ser.write(b'Q')
    elif user_response == "turn on light3":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning On Light 3.")
        ser.write(b'E')
        
        
    elif user_response == "turn on light4":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning On Light 4.")
        ser.write(b'T')
        

    if user_response == "turn off light1":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning Off Light 1.")
        ser.write(b'M')
        
        
    if user_response == "turn off light2":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning Off Light 2.")
        ser.write(b'N')
        

    if user_response == "turn off light3":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning Off Light 3.")
        ser.write(b'Y')
        

    if user_response == "turn off light4":
        # Send a confirmation message
        bot.send_message('5084417621', "Ok Turning Off Light 4.")
        ser.write(b'I')
        

# Function to run the bot polling in a separate thread
def run_bot_polling():
    bot.polling()

# Start the bot polling in a separate thread
bot_thread = threading.Thread(target=run_bot_polling)
bot_thread.start()

# Inside your while loop:
while True:

    ret, frame = cap.read()

    # Convert the frame to grayscale (dlib works on grayscale images)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the grayscale frame
    faces = detector(gray)

    # Initialize counters for faces in two different locations
    total_faces_left = 0
    total_faces_right = 0

    # Set location to None if no faces are detected
    location = None

    # Iterate over detected faces
    for face in faces:
        # Get facial landmarks for each detected face
        landmarks = predictor(gray, face)

        # Calculate the center of the face
        x, y = landmarks.part(30).x, landmarks.part(30).y  # Using the nose tip (landmark 30) as the reference point

        # Determine if the face is on the left or right side of the frame
        if x < frame.shape[1] // 2:
            total_faces_left += 1
            location = "left"  # Face is on the left side
        else:
            total_faces_right += 1
            location = "right"  # Face is on the right side

        # Draw rectangles around the detected faces
        x, y, w, h = face.left(), face.top(), face.width(), face.height()
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Draw facial landmarks
        for i in range(68):  # Assuming we're using the 68-point facial landmarks model
            x, y = landmarks.part(i).x, landmarks.part(i).y
            cv2.circle(frame, (x, y), 2, (0, 0, 255), -1)

    # Check if the location has changed from the previous frame
    if prev_location is not None:
        if prev_location == "right" and location == "left":
            print("Transitioned from right to left")
            if A > 0:
                A -= 1
                if A == 0:
                    # Send "Do you want to turn off all the lights?" message
                    bot.send_message('5084417621', "Do you want to turn off all the lights? Reply with ' yes ' or ' no '.")

        elif prev_location == "left" and location == "right":
            print("Entered In Room")
            A += 1
            if A == 1:
                # Send "Welcome to the room" message
                bot.send_message('5084417621', "Welcome to the room! Basic lightings are on. You can turn on or off the custom lights.")
                ser.write(b'P')
                location = None

    # Update the previous location
    prev_location = location

    # Ensure A remains non-negative
    A = max(0, A)

    # Display the total number of detected faces in left and right ROIs
    cv2.putText(frame, f'Faces Left: {total_faces_left}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    cv2.putText(frame, f'Faces Right: {total_faces_right}', (frame.shape[1] // 2 + 10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Display the value of A
    cv2.putText(frame, f'A: {A}', (10, 70), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Display the location status
    cv2.putText(frame, f'Location: {location}', (10, 110), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Display the frame with detected faces and landmarks
    cv2.imshow('Face Detection and Landmarks', frame)

    # Exit the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# Release the webcam and close all OpenCV windows
cap.release()
cv2.destroyAllWindows()
