#include<Ultrasonic.h>
int distance;
Ultrasonic ultrasonic(12,13);
void setup(){
Serial.begin(9600);
pinMode(13,OUTPUT);   //left motors forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(10,OUTPUT);   //right motors reverse
}
void loop(){
distance= ultrasonic.read;
Serial.print(distance);
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
  digitalWrite(12,HIGH);
}
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(10,HIGH);
}
if(distance<50){
   digitalWrite(13,LOW);
  digitalWrite(12,LOW);
    digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  delay(900);
    digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
  
}

}
