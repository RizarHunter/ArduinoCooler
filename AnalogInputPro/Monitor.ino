void monitorSetup() {
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_LIME);
  monitorTextColorWhite();
  myGLCD.clrScr();
}

void monitorUpdate() {
  if (millisecond % 10 == 0) {
    if (isDeveloperMenu)
      makeTextDev(); // Меню розробника
    else {
      switch (state) {
        case -1: {
            makeTextCalibrationTemperature();
          } break; // Калибровка температури
        case  0: {
            makeTextMainMenu();
          } break; // Main Menu
        case  1: {
            makeTextCalibration();
          } break; // Калибровка
        case  2: {
            makeTextPause();
          } break; // пауза
        case  3: {
            makeTextWork();
          } break; // Робота
        case  4: {
            
          } break; // Special Menu ** Only for dev menu  
        default: {} break;
      }
    }
  }
}



void monitorTextColorWhite() {
  myGLCD.setColor(VGA_WHITE);
}
void monitorTextColorYellow() {
  myGLCD.setColor(VGA_AQUA);
}
void monitorTextColorGreen() {
  myGLCD.setColor(VGA_LIME);
}
void monitorTextColorRed() {
  myGLCD.setColor(VGA_BLUE);
}
void cleanMonitor() {
  myGLCD.clrScr();
}


void makeTextCalibrationTemperature() {
  data = "Calibration";
  myGLCD.print(data, 0, 0);
  data = "temperature: ";
  myGLCD.print(data, 20, 20);
  data = (String)(100 * millisecondFromStartFullCalibration / timeCalibrationOfTemperature) + "%";
  myGLCD.print(data, 40, 40);
}

void makeTextMainMenu(){
  data = "Main menu";
  myGLCD.print(data, 20, 0);
  data = "temperature: " + (String)temperature;
  myGLCD.print(data, 10, 20);
  
  if (temperature < 10) { monitorTextColorRed(); data = "temperat very low"; }
  else if (temperature > 25) { monitorTextColorRed(); data = "temperat very high"; }
  else data = "temperature normal";
  myGLCD.print(data, 0, 32);
  monitorTextColorWhite();
  
  data = "1 - find temper again";
  myGLCD.print(data, 0, 60);
  data = "2 - main menu";
  myGLCD.print(data, 0, 72);
  data = "3 - calibrat " + calibrationIsDone;
  myGLCD.print(data, 0, 84);
  data = "4 - pause";
  myGLCD.print(data, 0, 96);
  data = "5 - start work";
  myGLCD.print(data, 0, 108);
}

void makeTextCalibration() {
  data = "Calibration: ";// + (String)temperature;
  myGLCD.print(data, 10, 0);
  data = "Power of Freez: " + (String)(howPowerfullWorkFreezer);
  myGLCD.print(data, 0, 20);
  //int perc = 100 * abs(needTemperature - temperature) / calibrationDifferenceTemperature;
  //data = (String)(perc) + "%  ";
  //myGLCD.print(data, 40, 40);
}

void makeTextPause() {
  data = "Temperature: " + (String)temperature;
  myGLCD.print(data, 0, 0);
  data = "TargetTempe: " + (String)targetTemperature;
  myGLCD.print(data, 0, 16);
  data = "Speed: " + (String)speedTemperature + " deg/min";
  myGLCD.print(data, 0, 32);
  data = ("-------PAUSE-------");
  myGLCD.print(data, 0, 64);
}

void makeTextWork() {
  data = "Temperature: " + (String)temperature;
  myGLCD.print(data, 0, 0);
  data = "TargetTempe: " + (String)targetTemperature;
  myGLCD.print(data, 0, 16);
  data = "Speed: " + (String)speedTemperature + " deg/min";
  myGLCD.print(data, 0, 32);
  data = ("--------WORK-------");
  myGLCD.print(data, 0, 64);
}

void makeTextDev() {
  data = "Tm: " + (String)temperature;
  myGLCD.print(data, 0, 0);
  data = "Res: " + (String)average;
  myGLCD.print(data, 0, 12);
  data = "NdTm: " + (String)needTemperature + " d:" + (String)(temperature - needTemperature);
  myGLCD.print(data, 0, 24);
  data = "TrgTm: " + (String)targetTemperature;
  myGLCD.print(data, 0, 36);
  data = "Sp: " + (String)speedTemperature;
  myGLCD.print(data, 0, 48);
  data = "Sp: " + (String)speedTemperatureSmall + " (" + (String)speedTemperatureBig + ")  ";
  myGLCD.print(data, 0, 60);
  data = "S1.Fr: " + (String)coefSourceFreez + " " + (String)(howPowerfullWorkFreezer);
  myGLCD.print(data, 0, 72);
  data = "S2.He: " + (String)coefSourceHeater + " " + (String)(howPowerfullWorkHeater);
  myGLCD.print(data, 0, 84);
  data = "State: " + (String)state;
  myGLCD.print(data, 0, 96);
  data = ""
         + getTimeTwoDigits(hour) + ":"
         + getTimeTwoDigits(minute) + ":"
         + getTimeTwoDigits(second) + ":"
         + (String)(millisecond) + " ;;";
  data += (String)counter;
  myGLCD.print(data, 0, 108);
}
