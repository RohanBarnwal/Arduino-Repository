#include<Ultrasonic.h>
int distance;
Ultrasonic ultrasonic(12,13);
void setup(){
Serial.begin(9600);
}
void loop(){
distance=ultrasonic.read;
Serial.print("distance");
Serial.println("distance");
delay(1000);
}
