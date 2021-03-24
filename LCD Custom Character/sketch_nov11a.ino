#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte smiley[8] = {
 B00110,
  B00001,
  B11111,
  B00101,
  B11001,
  B10001,
  B01001,
  B00101
};
byte r[8] ={
    B11111,
  B01100,
  B10000,
  B01110,
  B10001,
  B10010,
  B01000,
  B00100
};

void setup() {
  lcd.createChar(0, smiley);
  lcd.createChar(1,r);
 lcd,setCursor(0,0);
 lcd.begin(16,2);
}

void loop() {}
