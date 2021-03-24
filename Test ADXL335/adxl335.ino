const int xpin=A0;
const int ypin=A1;
const int zpin=A2;
void setup(){
  Serial.begin(9600);
  
}
void loop(){
  int x= analogRead(xpin);
  delay(1000);
  int y= analogRead(ypin);
  delay(1000);
  int z= analogRead(zpin);

  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
}
