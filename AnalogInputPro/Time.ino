void timeSetup(){
  millisecondOfNewCalibration = 0;
}

void timeUpdate() {
  getMillis();
  findTime();
  timeAfterCalibration();
}

void getMillis(){
  millisecondCommon = millis();
}

void findTime(){
  millisecondLast = millisecond;
  millisecond = millisecondCommon % thousand;
  second = millisecondCommon / thousand % 60;
  minute = millisecondCommon / thousand / 60 % 60;
  hour = millisecondCommon / thousand / 60 / 60;
}

void timeAfterCalibration(){
  millisecondFromStartFullCalibration = millisecondCommon - millisecondOfNewCalibration;
}


void startNewTimeCalibration(){
  millisecondOfNewCalibration = millisecondCommon;
  millisecondFromStartFullCalibration = 0;
}
