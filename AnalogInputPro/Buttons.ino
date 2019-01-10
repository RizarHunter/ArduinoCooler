void buttonsSetup(){
  
}
void buttonsUpdate(){
  lastButtonPushed();
  getButtons();
}

void getButtons(){
  key = keypad.getKey();
  
  if (Serial.available() > 0)
    key = (char)(Serial.readString()[0]);
}

void lastButtonPushed(){
  if (key){
    lastLongTouchKey = key;
    lastSymbols(key);
  }  
  lastKey = key;
}

void lastSymbols(char key){ // Запис останнього символа в стек
  for (i = symbols - 1; i > 0; i--) {
    keyMass[i] = keyMass[i-1];
  }
  keyMass[0] = key;
}
