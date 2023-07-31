#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the pin for the LED
const int ledPin = 13;

// Define the pin for the push button to reset the program
const int resetButtonPin = 2;

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin not used for this OLED module

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variable to store incoming data from Serial
char incomingData;

// Variable to keep track of eye closure start time
unsigned long eyeClosedStartTime = 0;

// Variable to keep track of yawn start time
unsigned long yawnStartTime = 0;

// Duration in milliseconds to consider it as a blink (adjust as needed)
const unsigned long blinkDuration = 1000; // 1 second

// Duration in milliseconds to consider it as a yawn (adjust as needed)
const unsigned long yawnDuration = 3000; // 3 seconds

// Duration in milliseconds to start the countdown timer after 5 seconds of continuous eye blink
const unsigned long countdownTimerDuration = 5000; // 5 seconds

// Flag to indicate if the countdown timer is active for blinking
bool countdownTimerActive = false;

// Flag to indicate if the countdown timer is active for yawning
bool yawningCountdownActive = false;

// Variable to keep track of the number of times cancel button is pressed
int cancelButtonPressCount = 0;

// Function to reset all states to initial values
void resetStates() {
  countdownTimerActive = false;
  yawningCountdownActive = false;
  eyeClosedStartTime = 0;
  yawnStartTime = 0;
  cancelButtonPressCount = 0;

  // Clear the display and show the welcome message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Eye Blink and Yawn");
  display.println("    Detection");
  display.display();
  delay(2000);
  display.clearDisplay();
}

// Function to display a message on the OLED screen
void displayMessage(const char* message) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
  delay(2000);
  display.clearDisplay();
}

// Function to display the countdown value on the OLED screen
void displayCountdown(int countdownValue) {
  display.clearDisplay();
  display.setTextSize(2); // Increase text size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20); // Center the countdown text
  display.print(countdownValue);
  display.display();
}

// Function to display the countdown value for yawning on the OLED screen
void displayYawnCountdown(int countdownValue) {
  display.clearDisplay();
  display.setTextSize(2); // Increase text size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20); // Center the countdown text
  display.print(countdownValue);
  display.display();
}

void setup() {
  // Initialize Serial communication with a baud rate of 9600
  Serial.begin(9600);

  // Initialize the LED pin as an OUTPUT
  pinMode(ledPin, OUTPUT);

  // Initialize the reset button pin as an INPUT with internal pull-up resistor
  pinMode(resetButtonPin, INPUT_PULLUP);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  // Display welcome message
  resetStates();
}

void loop() {
  // Check if there is any data available to read from Serial
  if (Serial.available() > 0) {
    // Read the incoming data from Serial
    incomingData = Serial.read();

    // If the received data is '1', it indicates closed eyes
    if (incomingData == '1') {
      // Check if the eye closure start time is not already recorded
      if (eyeClosedStartTime == 0) {
        // Record the start time of eye closure
        eyeClosedStartTime = millis();
      }

      // Check if the eye closure duration is greater than the blink duration
      if (millis() - eyeClosedStartTime > blinkDuration) {
        // Blink duration exceeds the threshold, consider it as a blink
        displayMessage("Blink detected!");

        // Reset the eye closure start time to prepare for the next blink detection
        eyeClosedStartTime = 0;

        // Check if the countdown timer is active
        if (countdownTimerActive) {
          // Display cancellation message
          displayMessage("Countdown Cancelled");

          // Increment the cancel button press count
          cancelButtonPressCount++;

          // Check if the cancel button was pressed more than 2 times
          if (cancelButtonPressCount > 2) {
            // Reset all states to initial values
            resetStates();
          }
        } else {
          // Start the countdown timer for blinking
          countdownTimerActive = true;
          unsigned long countdownStartTime = millis();
          unsigned long elapsedTime;

          while (countdownTimerActive) {
            // Check if the reset button is pressed to reset the program
            if (digitalRead(resetButtonPin) == LOW) {
              // Reset the program when the button is pressed
              resetStates();
              break;
            }

            // Calculate elapsed time for the countdown
            elapsedTime = millis() - countdownStartTime;
            if (elapsedTime >= countdownTimerDuration) {
              // Countdown is complete, send the email or perform any other action
              displayMessage("Email Sent!");
              countdownTimerActive = false;
              resetStates();
              break;
            } else {
              // Display the countdown for blinking
              int countdownValue = (countdownTimerDuration - elapsedTime) / 1000;
              displayCountdown(countdownValue);
            }
          }
        }
      }
    } else if (incomingData == '2') {
      // If the received data is '2', it indicates a yawn
      // Check if the yawn start time is not already recorded
      if (yawnStartTime == 0) {
        // Record the start time of yawn
        yawnStartTime = millis();
      }

      // Check if the yawn duration is greater than the yawn duration
      if (millis() - yawnStartTime > yawnDuration) {
        // Yawn duration exceeds the threshold, consider it as a yawn
        displayMessage("Yawn detected!");

        // Reset the yawn start time to prepare for the next yawn detection
        yawnStartTime = 0;

        // Start the countdown timer for yawning
        int yawningCountdownValue = 5;
        while (yawningCountdownValue >= 0) {
          // Check if the reset button is pressed to reset the program
          if (digitalRead(resetButtonPin) == LOW) {
            // Reset the program when the button is pressed
            resetStates();
            return;
          }

          // Display the countdown for yawning
          displayYawnCountdown(yawningCountdownValue);
          delay(1000); // Wait for 1 second before updating the countdown value
          yawningCountdownValue--;
        }

        // After the countdown is complete, send the email or perform any other action
        displayMessage("Email Sent!");
        resetStates();
      }
    } else {
      // If the received data is anything other than '1' or '2', it indicates open eyes or no yawn
      // Reset the eye closure start time and yawn start time
      eyeClosedStartTime = 0;
      yawnStartTime = 0;
    }
  }
}
