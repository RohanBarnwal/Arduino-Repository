// Define the pins for your lights
const int light1Pin = 2;  // Change to the actual pin number for light 1
const int light2Pin = 3;  // Change to the actual pin number for light 2
const int light3Pin = 4;  // Change to the actual pin number for light 3
const int light4Pin = 5;  // Change to the actual pin number for light 4

char command; // Variable to store incoming commands

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize light pins as outputs
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  pinMode(light3Pin, OUTPUT);
  pinMode(light4Pin, OUTPUT);

  // Initially, turn off all lights
  digitalWrite(light1Pin, HIGH);
  digitalWrite(light2Pin, HIGH);
  digitalWrite(light3Pin, HIGH);
  digitalWrite(light4Pin, HIGH);
}

void loop() {
  // Check for incoming serial data
  if (Serial.available() > 0) {
    command = Serial.read(); // Read the incoming command
    
    // Process the command
    if (command == 'D') {
      // Turn off all lights
      digitalWrite(light1Pin, HIGH);
      digitalWrite(light2Pin, HIGH);
      digitalWrite(light3Pin, HIGH);
      digitalWrite(light4Pin, HIGH);
    } else if (command == 'P') {
      // Turn on light 1
      digitalWrite(light1Pin, LOW);
      delay(1000); // Delay to keep the light on for some time (1 second in this case)
      digitalWrite(light1Pin, LOW); // Turn off light 1 after delay
    } else if (command == 'Q') {
      // Turn on light 2
      digitalWrite(light2Pin, LOW);
      delay(1000);
      digitalWrite(light2Pin, LOW);
    } else if (command == 'E') {
      // Turn on light 3
      digitalWrite(light3Pin, LOW);
      delay(1000);
      digitalWrite(light3Pin, LOW);
    } else if (command == 'T') {
      // Turn on light 4
      digitalWrite(light4Pin, LOW);
      delay(1000);
      digitalWrite(light4Pin, LOW);
    } else if (command == 'M') {
      // Turn off light 1
      digitalWrite(light1Pin, HIGH);
    } else if (command == 'N') {
      // Turn off light 2
      digitalWrite(light2Pin, HIGH);
    } else if (command == 'Y') {
      // Turn off light 3
      digitalWrite(light3Pin, HIGH);
    } else if (command == 'I') {
      // Turn off light 4
      digitalWrite(light4Pin, HIGH);
    }
  }
}
