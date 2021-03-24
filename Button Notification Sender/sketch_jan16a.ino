#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "wK86ZlK8cJnfDUlRGNAGEPs1QXRzYxRv";


char ssid[] = "";
char pass[] = "";


void setup()
{
  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  Blynk.notify("She pressed the BUTTON!");
delay(1000);


ESP.deepSleep(0);
  
}

void loop()
{
  Blynk.run();
  
}
