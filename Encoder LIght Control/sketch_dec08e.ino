int led_pin = 5;
#define encoder0PinA 2
#define encoder0PinB 3
int encoder0Pos = 0;
void setup() {
  //Declaring LED pin as output
  pinMode(led_pin, OUTPUT);
    pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
}
void loop() {
  //Fading the LED
  for(int encoder0PinA=0; encoder0PinA<255; encoder0PinA++){
    analogWrite(led_pin, i);
    delay(5);
  }
  for(int i=255; i>0; i--){
    analogWrite(led_pin, i);
    delay(5);
  }
    if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB))
  {
  encoder0Pos++;
  }
  else
  {
  encoder0Pos--;
  }
  valRotary = encoder0Pos/2.5;
}
