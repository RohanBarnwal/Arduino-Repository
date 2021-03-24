#include <Keypad.h>

const byte ROWS = 4; //four rows

const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {

  {'1','2','3','A'},

  {'4','5','6','B' },

  {'7','8','9','C'},

  {'*','0','#','D'}

};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad

byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
     pinMode(13,OUTPUT);
}

void loop(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    Serial.println(key);
  }
  if(key=='1'){
    digitalWrite(10,HIGH);
  }
   if(key=='2'){
    digitalWrite(11,HIGH);
  }
   if(key=='3'){
    digitalWrite(12,HIGH);
  }
   if(key=='4'){
    digitalWrite(13,HIGH);
  }
   if(key=='0'){
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW
    
    
    
    ;
  }
}
