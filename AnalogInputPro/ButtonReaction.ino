void buttonReactionSetup() {

}

void buttonReactionUpdate() {
  if (isDeveloperMenu) {
    //joistReactiion();
    changeDependenciesKeyDevelop();
  }
  else {
    catchDevMenu();
    changeDependenciesKeyUsual();
  }
}




void joistReactiion() {
  axisX();
  axisY();
  //button();
}

void axisX() {
  speedTemperature += ((int)(positionX - 520) / (int)50) * 0.0005f;
  if (speedTemperature < 0) speedTemperature = 0;
}
void axisY() {
  targetTemperature -= ((int)(positionY - 520) / (int)50) * 0.075f;
  if (targetTemperature < temperatureMin) targetTemperature = temperatureMin;
  if (targetTemperature > temperatureMax) targetTemperature = temperatureMax;
}
void button() {}



void changeDependenciesKeyUsual() {
  if (isPushedNewButton('1')) button1Usu();
  if (isPushedNewButton('2')) button2Usu();
  if (isPushedNewButton('3')) button3Usu();
  if (isPushedNewButton('4')) button4Usu();
  if (isPushedNewButton('5')) button5Usu();
  if (isPushedNewButton('D')) buttonDUsu();
}

void button1Usu() {
  calibrateFirstTemperature();
}
void button2Usu() {
  stateMainMenu();
}
void button3Usu() {
  calibrateFreezer();
}
void button4Usu() {
  statePause();
}
void button5Usu() {
  stateWork();
}
void buttonDUsu() { // DeveloperMenu
  //makeDeveloperMenu();
}



void changeDependenciesKeyDevelop() {
  if (isPushedNewButton('1')) button1Usu();
  if (isPushedNewButton('2')) button2Usu();
  if (isPushedNewButton('3')) button3Usu();
  if (isPushedNewButton('4')) button4Usu();
  if (isPushedNewButton('5')) button5Usu();
  if (isPushedNewButton('6')) button6();
  if (isPushedNewButton('7')) button7();
  if (isPushedNewButton('8')) button8();
  if (isPushedNewButton('9')) button9();
  if (isPushedNewButton('0')) button0();
  if (isPushedNewButton('*')) buttonStar();
  if (isPushedNewButton('#')) buttonDiez();
  if (isPushedNewButton('A')) buttonA();
  if (isPushedNewButton('B')) buttonB();
  if (isPushedNewButton('C')) buttonC();
  if (isPushedNewButton('D')) buttonD();
}

bool isPushedNewButton(char k) {
  return (key == k && lastKey != k);
}

void button1() {}
void button2() {}
void button3() {}
void button4() {}
void button5() {}
void button6() {
  stateSpecil();
}
void button7() {
    targetTemperature -= 50;
  if (targetTemperature < temperatureMin) targetTemperature = temperatureMin;
  if (targetTemperature > temperatureMax) targetTemperature = temperatureMax;  
}
void button8() {
  targetTemperature = temperatureMin;
}
void button9() {
  targetTemperature += 50;
  if (targetTemperature < temperatureMin) targetTemperature = temperatureMin;
  if (targetTemperature > temperatureMax) targetTemperature = temperatureMax;  
}
void button0() {
  if (speedTemperature == 0) {
    speedTemperature = 1;
  }
  else {
    speedTemperature = 0;
  }
}
void buttonStar() { 
  speedTemperature *= 0.9f;
  if (speedTemperature < 0) speedTemperature = 0;  
}
void buttonDiez() {
  speedTemperature *= 1.1;
  if (speedTemperature < 0) speedTemperature = 0;
}
void buttonA() {
  howPowerfullWorkFreezer += 100;
  if (howPowerfullWorkFreezer > 1000) 
    howPowerfullWorkFreezer = 1000;
}
void buttonB() {
  howPowerfullWorkFreezer = 0;
}
void buttonC() {
  howPowerfullWorkFreezer -= 100;
  if (howPowerfullWorkFreezer < 0) 
    howPowerfullWorkFreezer = 0;
}
void buttonD() { // DeveloperMenu
  
  if (state == 4) stateMainMenu();
  makeNotDeveloperMenu();
}


void catchDevMenu(){ // Перевырка чи залогынено для меню розробника
  checkSymbols();
}
void checkSymbols(){ // Перевырка чи сходиться пароль
  for (i = 0 ; i < symbols; i++ ){
    if (keyPaswordSIMPLE[i] != keyMass[i])
     way = SIMPLE;
  }
  for (i = 0 ; i < symbols; i++ ){
    if (keyPaswordWITHslowPART[i] != keyMass[i])
     way = WITHslowPART;
  }
  for (i = 0 ; i < symbols; i++ ){
    if (keyPasword[i] != keyMass[i])
     return;
  }
  resetKeyMass(); 
  makeDeveloperMenu();
}
void resetKeyMass(){ // Збити всы кнопкы на пусты
  for (i = 0;i<symbols; i++){
    keyMass[i]=' ';
  }
}


void workOrPause(){
  if (state = -1) {}
  else if (state = 0) {}
  else if (state == 1) stateWork();
  else if (state == 2) statePause();
}

void makeDeveloperMenu() {
  isDeveloperMenu = true;
  myGLCD.setFont(SmallFont);
  makeColorMenu();
}
void makeNotDeveloperMenu() {
  isDeveloperMenu = false;
  myGLCD.setFont(BigFont);
  makeColorMenu();
}

void stateMainMenu(){
  state = 0;
  makeColorMenu();
}
void stateWork(){
  state = 3;
  makeColorMenu();
}
void statePause(){
  state = 2;
  makeColorMenu();
}
void stateSpecil(){
  state = 4;
  makeColorMenu();
}
void calibrateFreezer(){
  state = 1;
  makeColorMenu();
}
void calibrateFirstTemperature() {
  state = -1;
  startNewTimeCalibration();
  makeColorMenu();
}

void makeColorMenu() {
  cleanMonitor();
  if (isDeveloperMenu) {
    monitorTextColorYellow();
  }
  else {
    switch (state){
      case -1 : { monitorTextColorWhite(); } break;
      case 0 : { monitorTextColorWhite(); } break;
      case 1 : { monitorTextColorWhite(); } break;
      case 2 : { monitorTextColorWhite(); } break;
      case 3 : { monitorTextColorGreen(); } break;
      case 4 : { monitorTextColorRed(); } break;
      default : {  } break;
    } 
  }
}
