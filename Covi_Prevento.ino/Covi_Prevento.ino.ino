#include <Wire.h>
#include <Adafruit_MLX90614.h>                                                                                                                                                                                                                                                                                                                  //Created By Rohan Barnwal
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "kb1Za91DbYpD0tGysNe5jKaHm_Toxj5m"; //Auth code sent via Email
char ssid[] = "Rohan"; //Wifi name
char pass[] = "1234567890";  //Wifi Password
Adafruit_MLX90614 mlx = Adafruit_MLX90614();//Making a variable mlx
void notifyOnThings(){
  if(mlx.readObjectTempC()< 37 && mlx.readObjectTempC()>33)//mlxreadObjectTempC means the reading of Object Temperature
  { 
    digitalWrite(D4,HIGH);
    digitalWrite(D3,LOW);
     Blynk.notify( "कोई दिक्कत नहीं है" );//Notification when temperature is normal
  
      
  }

 
  else if(mlx.readObjectTempC()>38) {
       digitalWrite(D3,HIGH);
       digitalWrite(D4,LOW);
    Blynk.notify("सतर्कता बनाए रखे");//Notification when temperature is high
        
  
  }
  else{
    digitalWrite(D4,LOW);
    digitalWrite(D3,LOW);
  }
 

}

void setup() {
  
Serial.begin(9600);//Serial Monitor means a monitor from where you can read the values
Blynk.begin(auth, ssid, pass); 
pinMode(D4,OUTPUT);
pinMode(D3,OUTPUT);
timer.setInterval(50L,notifyOnThings); 
  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); Serial.println("*C");


  Serial.println();
  
   Blynk.run();
  timer.run();
}

//Created By Rohan Barnwal
