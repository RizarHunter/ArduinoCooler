void sensorSetup() {
  pinMode(THERMISTORPIN, INPUT);
  firstMoment();
  setDefaultMassiveTemperature(defaultTemperatureFromStart);
}
void sensorUpdate() {
  if (millisecondFromStartFullCalibration < 40) firstMoment(); // Write all massive, if first moment
  if (abs(millisecond - millisecondSensor) > 20) {
    getData();
    sensorTimeUpdate();
  }
  calculateAverage();
  calculateTemperature();

  temperatureMassiveAndSpeed();
}

void firstMoment() {
  for (i = 0; i < periodMiddle; i++) {
    samples[i] = analogRead(THERMISTORPIN);
  }
}
void setDefaultMassiveTemperature(float defaultTemperatureFromStart){
  for (i = 0; i < numberOfSecondForTemperature; i++) {
    tempertatureForEverySecond[i] = defaultTemperatureFromStart;
  }
}

void getData() {
  for (i = 0; i < periodMiddle - 1; i++) {
    samples[i] = samples[i + 1];
  }
  samples[periodMiddle - 1] = analogRead(THERMISTORPIN);
}
void sensorTimeUpdate() {
  millisecondSensor = millisecond;
}

void calculateAverage() {
  average = 0;
  for (i = 0; i < periodMiddle; i++) {
    average += samples[i];
  }

  average /= periodMiddle;
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
}

void calculateTemperature() {
  lastTemperature = temperature; \
  temperature = (average - 100) * 2.5f;
  //temperature = (average - 19) * 2.56f - 196;
  temperature = (temperature + lastTemperature) / 2;
}



void temperatureMassiveAndSpeed(){
  saveTemperature();
  updateSpeedOfTemperature();
}

void saveTemperature() {
  if ((second + 60 - commonTimeLastMesuare) % 60 > 0) {
    saveTemperatureInMassive();
    commonTimeLastMesuare = second;
  }
}
void saveTemperatureInMassive() {
  for (i = numberOfSecondForTemperature - 1; i > 0; i--) {
    tempertatureForEverySecond[i] = tempertatureForEverySecond[i - 1];
  }
  tempertatureForEverySecond[0] = lastTemperature;
}
void updateSpeedOfTemperature(){
  int howManyNumbers = 5; // amount for averaging
  
  float firstNumber = tempertatureForEverySecond[0];
  for (i = 1; i < howManyNumbers; i++){ firstNumber += tempertatureForEverySecond[i]; }
  if (howManyNumbers > 0) firstNumber /= howManyNumbers;
  
  float lastSmallNumber = tempertatureForEverySecond[numberOfSecondForTemperatureSmall - 1];
  for (i = numberOfSecondForTemperatureSmall - howManyNumbers; i < numberOfSecondForTemperatureSmall - 1; i++){ lastSmallNumber += tempertatureForEverySecond[i]; }
  if (howManyNumbers > 0) lastSmallNumber /= howManyNumbers;
  
  float lastBigNumber = tempertatureForEverySecond[numberOfSecondForTemperature - 1];
  for (i = numberOfSecondForTemperature - howManyNumbers; i < numberOfSecondForTemperature - 1; i++){ lastBigNumber += tempertatureForEverySecond[i]; }
  if (howManyNumbers > 0) lastBigNumber /= howManyNumbers;
  
  speedTemperatureSmall = (lastSmallNumber - firstNumber)
   / (numberOfSecondForTemperatureSmall - 1) * 60;
  speedTemperatureBig = (lastBigNumber - firstNumber)
   / (numberOfSecondForTemperature-1) * 60;
}
