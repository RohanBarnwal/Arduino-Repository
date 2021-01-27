#include <Wire.h>
#include <Adafruit_MLX90614.h>
//Created By Rohan Barnwal                                                                                                                                                                                                                                                                                                                    //Created By Rohan Barnwal
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "613r1JkkTLLrrEhLRn9apr-b0wv0AS_4"; //Auth code sent via Email
char ssid[] = "Rohan"; //Wifi name
char pass[] = "rohanbarnwal";  //Wifi Password
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void notifyOnThings(){
  if(mlx.readObjectTempC()< 37 && mlx.readObjectTempC()>33)
  { 
    digitalWrite(D4,HIGH);
    digitalWrite(D3,LOW);
     Blynk.notify( "कोई दिक्कत नहीं है" );
  
      
  }

 
  else if(mlx.readObjectTempC()>38) {
       digitalWrite(D3,HIGH);
       digitalWrite(D4,LOW);
    Blynk.notify("सतर्कता बनाए रखे");
        
  
  }
  else{
    digitalWrite(D4,LOW);
    digitalWrite(D3,LOW);
  }
 

}

void setup() {
  Serial.begin(9600);
Serial.begin(9600);
Blynk.begin(auth, ssid, pass); 
pinMode(D4,OUTPUT);
pinMode(D3,OUTPUT);
timer.setInterval(50L,notifyOnThings); 
  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); Serial.println("*C");


  Serial.println();
  
   Blynk.run();
  timer.run();
}

//Created By Rohan Barnwal
//Created By Rohan Barnwal
//Created By Rohan Barnwal
//Created By Rohan Barnwal

  
