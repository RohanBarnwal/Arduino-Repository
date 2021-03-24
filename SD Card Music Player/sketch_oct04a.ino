#include"SD.h"
#define SD_ChipSelectPin 4
#include"TMRpcm.h"
#include"SPI.h"
TMRpcm tmrpcm;
void setup(){
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin)){
    Serial.println("SD FAIL");
    return;
  }
  tmrpcm.setVolume(5);
  tmrpcm.play("9.wav");
  
}

void loop(){
  
}