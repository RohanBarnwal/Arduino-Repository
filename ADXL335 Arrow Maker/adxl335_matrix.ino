const int xpin=A0;
const int ypin=A1;
const int zpin=A2;
      #include <LedControl.h>

int DIN = 8;
int CS =  9;
int CLK = 10;


LedControl lc=LedControl(DIN,CLK,CS,0);
void setup(){
  Serial.begin(9600);
  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,20);      // Set the brightness to maximum value
 lc.clearDisplay(0);      
}
void loop(){
  int x= analogRead(xpin);
  delay(100);
  int y= analogRead(ypin);
  delay(100);
  int z= analogRead(zpin);

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n ");
  byte left[8]={B00000000,
B00010000,
B00100000,
B01111111,
B00100000,
B00010000,
B00000000,
B00000000};
byte down[8]=
{B00010000,
B00010000,
B00010000,
B00010000,
B00010000,
B01010100,
B00111000,
B00010000};
  byte up[8]={B00000100,
B00001110,
B00010101,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100};
byte right[8]=
  {B00000000,
B00000100,
B00000010,
B01111111,
B00000010,
B00000100,
B00000000,
B00000000};   


if(x>250 && x<270){
  printByte(left);
  delay(1000);
}
if(x>330 && x<340){
  printByte(down);
  delay(1000);
}
if(z>360 && z<380){
  printByte(up);
  delay(1000);
}
if(y>310 && y<340){
  printByte(right);
  delay(1000);
}
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
