void processRullSetup() { }

void processRullUpdate() {
  switch (state) {
    case -1: { findFirstTemperature(); } break;// Find Temperature
    case 0: { pauseWork(); } break; // Main menu
    case 1: { testTemperature(); } break; // Calibration
    case 2: { pauseWork(); } break;// Pause
    case 3: { // Work
        minusTemperature();
        controlSourcePower();
        stateRelay();
      } break;
    case 4: { 
        minusTemperature();
        controlSourcePower();
        } break; // Special Work, потрыбна температура зменшуэться, але джерело охолодження не корегуэться
    default: {} break;
  }
}

void findFirstTemperature() {
  needTemperature = temperature;
  if (millisecondFromStartFullCalibration > timeCalibrationOfTemperature){
    stateWork();
  }
}

void testTemperature() {
  howPowerfullWorkFreezer = 500 * (1 - (1 / calibrationDifferenceTemperature) * (needTemperature - temperature));
  if (abs(needTemperature - temperature) > calibrationDifferenceTemperature){
    stateMainMenu();
    calibrationIsDone = "DONE";
  }
}

void pauseWork() {
  howPowerfullWorkFreezer = 0;
  howPowerfullWorkHeater = 0;
}


void minusTemperature() {
  if ((abs(targetTemperature - needTemperature) >= 0.1)
    /*&& (needTemperature + 6 > lastTemperature)*/) {
    needTemperature += 
      speedTemperature 
        * (((thisTimeSecond + 60) - lastTimeSecond) % 60)
        * temperatureCoef 
        * ((targetTemperature - needTemperature) / abs(targetTemperature - needTemperature));
  }
}


void controlSourcePower() {
  powerSource = (temperature - needTemperature);
}


void stateRelay() {
  if (powerSource > 0) {
    howPowerfullWorkFreezer = abs(powerSource) * coefSourceFreez;
    howPowerfullWorkHeater = 0;
  }
  else {
    howPowerfullWorkFreezer = 0;
    howPowerfullWorkHeater = abs(powerSource) * coefSourceFreez;
  }
}





void styles(){
  
}

void styleSIMPLE(){
  
}
void styleWITHslowPART(){
   
}
void stylePROGRESSIVE(){
  
}
