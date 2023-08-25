#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1); // Set text size to 1
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Safety Mode is Off");
  display.setTextSize(2); // Set text size to 2 for numbers
  display.setCursor(45, 25); // Adjust position for numbers
  display.println("100");
  display.display();
}

void loop() {
    if (Serial.read()== 'D') {
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("Safety Mode is On");
      display.setTextSize(2); // Set text size to 2 for numbers
      display.setCursor(45, 25); // Adjust position for numbers
      display.println("50");
      display.display();
      display.display();
      
     

    } else if (Serial.read()== 'B') {
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("Safety Mode is Off");
      display.setTextSize(2); // Set text size to 2 for numbers
      display.setCursor(45, 25); // Adjust position for numbers
      display.println("100");
      display.display();
      display.display();
      

    }
  }
