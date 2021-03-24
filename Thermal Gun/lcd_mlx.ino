/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1747 3V version
  ----> https://www.adafruit.com/products/1748 5V version

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal lcd(12,11,5,4,3,2);
void setup() {
  Serial.begin(9600);
lcd.begin(16,2);
  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
lcd.setCursor(0,0);
lcd.print("TempA:- ");
lcd.print(mlx.readAmbientTempC());lcd.print("*C");
lcd.setCursor(0,1);
lcd.print("TempO:- ");
lcd.print(mlx.readObjectTempC());lcd.print("*C");

  Serial.println();
  
}
