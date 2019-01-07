void joistSetup(){
  pinMode(SW, INPUT);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
}
void joistUpdate(){
  getJoistData();
}

void getJoistData(){
  positionX = analogRead(VRX);
  positionY = analogRead(VRY);
  pushThis = digitalRead(SW);
}
