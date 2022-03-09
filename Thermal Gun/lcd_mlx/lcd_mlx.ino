#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  mlx.begin();  
}

void loop() {
  lcd.print("Ambient = "); lcd.print(mlx.readAmbientTempC()); 
  lcd.print("*C\tObject = "); lcd.print(mlx.readObjectTempC()); Serial.println("*C");


  
}
