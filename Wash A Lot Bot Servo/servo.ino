#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

//this is the threshold where the sensor will trigger the 
//countdown. If you are getting extra countdowns or the 
//countdown won't start, you may need to adjust this for your sink
int threshold = 200;
Servo countServo;

void setup() {

  Serial.begin(9600);
  
  //attach pin 7 to servo and sweep it to indicate that the timer is on
  countServo.attach(7);
  countServo.write(180);
  delay(700);
  countServo.write(0);
  delay(700);
  countServo.write(180);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.println(distance);

  if (distance < threshold) {
    countdownServo();
  }
  delay(100);
}



//this moves the servo 4.5 degrees every half second
//to smooth out the movemnt (vs 9 degrees every second)
//for 20 seconds.
void countdownServo() {
  Serial.println("Counting down");
  int halfseconds = 40;

  for (int i = halfseconds; i >= 0; i--) {

    countServo.write((int)(i * 4.5));
    delay(500);
  }

  //reset the servo, clear the queue
  countServo.write(180);
  delay(700);
}
