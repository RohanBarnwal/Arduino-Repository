#include <Keypad.h>
 #include<Keyboard.h>
 #define KEY_LEFT_GUI      0x83
 char w= KEY_LEFT_GUI; 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
void setup() {
  // Setup serial monitor
  Serial.begin(9600);
   Keyboard.begin();
}
 
void loop() {
  // Get key value if pressed
  char customKey = customKeypad.getKey();
 
  if (customKeypad.getKey()=='5') {
Serial.print("gkgk");
  Keyboard.press(w);
  Keyboard.press('I');
delay(100);
Keyboard.releaseAll();
  
  
    
  }
}
