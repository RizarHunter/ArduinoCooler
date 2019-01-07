void freezerSetup() {
  pinMode(SOURCEFREEZ, OUTPUT);
}
void freezerUpdate() {
  workFreezer();
}

void workFreezer() {
  if (millisecond < howPowerfullWorkFreezer)
    digitalWrite(SOURCEFREEZ, HIGH);
  else
    digitalWrite(SOURCEFREEZ, LOW);
}
