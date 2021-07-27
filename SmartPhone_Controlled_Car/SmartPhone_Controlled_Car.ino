//Check this video to know about the whole things "https://youtu.be/SPF-p-8Q9rk"
//Created By Rohan Barnwal
char t;
 
void setup() {
pinMode(13,OUTPUT);   //left motors forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right motors forward
pinMode(10,OUTPUT);   //right motors reverse

pinMode(22,OUTPUT);   //Buzzer
pinMode(27,OUTPUT);   //Reverse Led
pinMode(25,OUTPUT);  //Reverse Led
pinMode(28,OUTPUT);  //Stop LED
pinMode(7,OUTPUT); //Stop LED
pinMode(32,OUTPUT); //Left Indicator
pinMode(34,OUTPUT); //Right Indicator
pinMode(2,OUTPUT);//Headlight
pinMode(3,OUTPUT);//Headlight
Serial.begin(9600);
 
}
 
void loop() {

if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(13,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(22,HIGH);
   digitalWrite(27,HIGH);
  digitalWrite(25,HIGH);
  digitalWrite(28,LOW);
  digitalWrite(7,LOW);
   digitalWrite(32,LOW);
  digitalWrite(34,LOW);
  digitalWrite(27,HIGH); //HL
digitalWrite(25,HIGH); //HL

}
 
else if(t == 'G'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(27,HIGH); //HL
digitalWrite(25,HIGH); //HL


  digitalWrite(10,HIGH);
    digitalWrite(27,LOW);
  digitalWrite(26,LOW);
  digitalWrite(28,LOW);
  digitalWrite(7,LOW);
   digitalWrite(25,LOW);
    digitalWrite(32,LOW);
  digitalWrite(34,LOW);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(12,HIGH);













  digitalWrite(27,HIGH);
  digitalWrite(26,LOW);
  digitalWrite(28,LOW);
  digitalWrite(32,HIGH); //HL
  digitalWrite(7,LOW); //HL
}


 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(10,HIGH);
  digitalWrite(27,LOW);
  digitalWrite(26,LOW);
      digitalWrite(28,LOW);
  digitalWrite(7,LOW);
  digitalWrite(32,LOW);
  digitalWrite(34,HIGH);//Right Indicator 
   digitalWrite(25,HIGH);//Right Indicator 
   return;
  
  
  
}

 else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(22,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(27,LOW);
  digitalWrite(26,LOW);
    digitalWrite(28,HIGH);//Stop LED
    digitalWrite(32,LOW);
  digitalWrite(34,LOW);
  digitalWrite(7,HIGH);//Stop LED
   digitalWrite(25,LOW);
}
else if(t=='X'){
  digitalWrite(27,HIGH);   //Reverse Led
digitalWrite(26,HIGH);  //Reverse Led
digitalWrite(28,HIGH);  //Stop LED
digitalWrite(7,HIGH); //Stop LED
digitalWrite(32,HIGH); //Left Indicator
digitalWrite(34,HIGH); //Right Indicator
digitalWrite(2,HIGH); //HL
digitalWrite(3,HIGH); //HL
 digitalWrite(25,HIGH);
}
else if(t=='Y'){
  digitalWrite(27,LOW);   //Reverse Led
digitalWrite(26,LOW);  //Reverse Led
digitalWrite(28,LOW);  //Stop LED
digitalWrite(7,LOW); //Stop LED
digitalWrite(32,LOW); //Left Indicator
digitalWrite(34,LOW); //Right Indicator
 digitalWrite(25,LOW);
digitalWrite(2,LOW); //HL
digitalWrite(3,LOW); //HL
}
else if(t=='M'){
  digitalWrite(2,HIGH); //HL
digitalWrite(3,HIGH); //HL
}
else if(t=='m'){
digitalWrite(2,LOW); //HL
digitalWrite(3,LOW); //HL



delay(100);
}
}
