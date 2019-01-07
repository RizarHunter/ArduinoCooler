void heaterSetup() {
  pinMode(SOURCEHEATER, OUTPUT);
}
void heaterUpdate() {

}

/*void relayRull() {
  controlSourcePower(); // Визначення різниці температури, між поточною і потрібною
  stateRelay(); // Робота релє
}

void controlSourcePower() {
  powerSource = (temperature - needTemperature);
}


void stateRelay() {
  if (!firstTime && isWork) {

    if (powerSource > 0) {
      numberOfSource = SOURCEFREEZ; // Якщо температура вище потрібної то джерело 1 - нагрівач в азоті
      coefChanger = coefSourceFreez;
      digitalWrite(SOURCEHEATER, LOW);
    }
    else {
      numberOfSource = SOURCEHEATER; // Якщо температура нижче потрібної то джерело 2 - нагрівач
      coefChanger = coefSourceHeater;
      digitalWrite(SOURCEFREEZ, LOW);
    }

    if (counter % 800 < abs(powerSource) * coefChanger)
      digitalWrite(numberOfSource, HIGH);
    else
      digitalWrite(numberOfSource, LOW);
  }
  else {
    digitalWrite(SOURCEFREEZ, LOW);
    digitalWrite(SOURCEHEATER, LOW);
  }
}*/
