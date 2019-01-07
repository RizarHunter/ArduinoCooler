void buttonsSetup(){
  
}
void buttonsUpdate(){
  lastButtonPushed();
  getButtons();
}

void getButtons(){
  key = keypad.getKey();
}

void lastButtonPushed(){
  if (key)
    lastLongTouchKey = key;  
  lastKey = key;
}
