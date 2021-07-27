#define BLYNK_PRINT Serial
 
 

#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 // V5 is the number of Virtual Pin  

BlynkTimer timer; // Announcing the timer
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ROHAN";
char pass[] = "oddo9707";

char auth[] = "b17RRaY0rtovOzg5bPi2DRxZ70dY-pob";
void myTimerEvent()
{
int  sensorData = analogRead(A0);
  Blynk.virtualWrite(V5, sensorData);
}

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
 
 
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
  
}
