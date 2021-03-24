 
//Created By Rohan Barnwal
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = " riLmZjnJp6Bt8FtAiEMftQU4tSSWmepw"; //Auth code sent via Email
char ssid[] = "Rohan"; //Wifi name
char pass[] = "rohanbarnwal";  //Wifi Password
int flag=0;
void notifyOnThings()
{
  int isButtonPressed = digitalRead(D1);
  if (isButtonPressed==1 && flag==0) {
    Serial.println("Rohan Someone in the House");
    Blynk.notify("रोहन कोई है तुम्हारे गेट में");
    flag=1;
  }
  else if (isButtonPressed==0)
  { 
    flag=0;
  }
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass); 
pinMode(D1,INPUT_PULLUP);
timer.setInterval(50L,notifyOnThings); 
}
void loop()
{
  Blynk.run();
  timer.run();
}
