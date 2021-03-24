int a=7;
void setup() {
  // put your setup code here, to run once:
pinMode(43,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(a)==HIGH){
  digitalWrite(43,HIGH);
  
}
else{
  digitalWrite(43,LOW);
}
}
