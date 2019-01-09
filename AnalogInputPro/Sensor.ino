void sensorSetup() {
  pinMode(THERMISTORPIN, INPUT);
  firstMoment();
}
void sensorUpdate() {
  if (millisecondFromStartFullCalibration < 40) firstMoment(); // Write all massive, if first moment
  if (abs(millisecond - millisecondSensor) > 20) { 
    getData();
    sensorTimeUpdate();
  }
  calculateAverage();
  calculateTemperature();
}

void firstMoment() {
  for (i = 0; i < periodMiddle; i++) {
    samples[i] = analogRead(THERMISTORPIN);
  }
}

void getData() {
  for (i = 0; i < periodMiddle - 1; i++) {
    samples[i] = samples[i + 1];
  }
  samples[periodMiddle - 1] = analogRead(THERMISTORPIN);
}
void sensorTimeUpdate(){
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
  lastTemperature = temperature;
  //temperature = (average - 102.6f) * 2.5f;
  temperature = (average - 102) * 2.45f;
  //temperature = (average - 19) * 2.56f - 196;
  temperature = (temperature + lastTemperature) / 2;
}
