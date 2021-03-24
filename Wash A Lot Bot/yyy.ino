//Created By Rohan Barnwal 
#include <Ultrasonic.h>
#include<LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Ultrasonic ultrasonic(8, 9);

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16,2);
  pinMode(13,OUTPUT);
}

void loop() {
  Serial.print("Distance in CM: ");
  Serial.println(ultrasonic.read());
  delay(10);

  if(ultrasonic.read()<10){
    lcd.setCursor(2,0);
    lcd.print("Time Started");
    int i;
    for(i=0;i<=30;i++){
      lcd.setCursor(7,1);
      lcd.print(i);
      delay(300);
      lcd.clear();
        lcd.setCursor(2,0);
    lcd.print("Time Started");
     }
    if(i=30){
      lcd.clear();
      lcd.setCursor(2,0);
       lcd.print("It's Done!!");
     lcd.setCursor(1,1);
       lcd.print("Please Reset");
       
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);

          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
          digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500); digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500); digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500); digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500); digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
         delay(500);
       }
    }
  }
