int i;
int touchStates;
void loop(){
  if(touchStates[i] == 0){
  //pin i was just touched
  Serial.print("pin ");
  Serial.print(i);
  Serial.println(" was just touched");


  switch (i) {
    case 0:
      //0 was touched

      break;
    case 1:
      //1 was touched

      break; 
    case 2:
      //2 was touched

      break; 
    case 3:
      //3 was touched
  }

}
}
