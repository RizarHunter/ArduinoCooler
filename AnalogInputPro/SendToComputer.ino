void sendToComputerSetup(){
  
}
void sendToComputerUpdate(){
  lastSecond();
  if (isToSendComputer){
    coefSourceChanger();
    //if (isDeveloperMenu) 
      sendMessage();
    isToSendComputer = false;
    lastTimeSecond = thisTimeSecond;
  }
  else{
    needSendDataToComputer();
  }
}

void lastSecond(){ 
  thisTimeSecond = second;
}

void needSendDataToComputer(){
  if (((thisTimeSecond + 60) - lastTimeSecond)%60 == sendToComputerPeriod) {
    isToSendComputer = true;
  }
  else{
    isToSendComputer = false;
  }
}

void coefSourceChanger(){
    message = "" 
    + getTimeTwoDigits(hour) + ":"
    + getTimeTwoDigits(minute) + ":"
    + getTimeTwoDigits(second) + ":"
    + (String)(millisecond) + " "
    + " Need: " + (String)needTemperature
    + "  Curent: " + (String)lastTemperature
    + " State: " + (String)(state)
    + " FreezPow: " + (String)(powerSource)
    + " FreezPer: " + (String)(howPowerfullWorkFreezer)
    + " SpeedTemperature: " + (String)speedTemperature
    //+ "       //"
    //+ " X:" + analogRead(VRX)
    //+ " Y:"+ analogRead(VRY)
    + "Button (" + lastLongTouchKey + ")(" + lastKey +")";
    ;
}

String getTimeTwoDigits(int number){
  if (number < 10) return "0" + (String)(number);
  else return (String)(number);
}

void sendMessage() {
  Serial.println(message);
}
