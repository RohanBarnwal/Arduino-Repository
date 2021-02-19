//Check this video to know about the whole things "https://youtu.be/SPF-p-8Q9rk"
//Created By Rohan Barnwal
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "OakOLED.h"
char t;

 int i=0;
 OakOLED oled;
void setup() {
pinMode(13,OUTPUT);   //left motors forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(10,OUTPUT);   //right motors reverse
pinMode(9,OUTPUT);   //Led
pinMode(2,INPUT); 
pinMode(23,OUTPUT);
Serial.begin(9600);
  oled.begin();


 
}
 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);

}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
}
 
else if(t == 'G'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(13,HIGH);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(11,HIGH);
}

else if(t == 'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
}
else if(t == 'w'){
  digitalWrite(9,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
}
if(digitalRead(2)==LOW){
  i=i+1;
  delay(500);
    oled.clearDisplay();
  Serial.println(i);
  delay(500);
  digitalWrite(23,HIGH);
  delay(200);
  digitalWrite(23,LOW);
  delay(200);
  
}
  oled.setTextSize(4);
  oled.setTextColor(1);
  oled.setCursor(50
  , 10);

  oled.println(i);
  
  oled.display();

}
