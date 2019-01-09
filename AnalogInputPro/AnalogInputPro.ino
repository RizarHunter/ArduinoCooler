#include <Keypad.h>
#include <memorysaver.h>
#include <UTFT.h>
//#include <SPI.h>
//#include <Wire.h>

enum Way{
  SIMPLE, 
  WITHslowPART, 
  PROGRESSIVE, 
};

int way = PROGRESSIVE;

//Common///////////////

int state = -1; // -1 - Юзтування температури, 0 - MainMenu, 1 - Юзтування, 2 - Пауза, 3 - Нормальна робота, 4 - SpecialWork
bool isCalibration = true; // Якшо true то юзтування, якщо false то нормальна робота
bool isWork = false; // Чи працюэ, чи пауза, true - work, false - pause
bool isDeveloperMenu = true;//false; // Запуск меню выдладки для розробникыв

#define timeRequest 1 // Час одного цикла
int i; // Лічильник циклів for
int counter; // Лічильник common

float temperature; // Поточна температура
float temperatureMax = 100; // Максимально можлива температура
float temperatureMin = -160; // Мынымально можлива температура
float targetTemperature = -150; // Температура до якої потрібно опустити
float needTemperature = 9999.99; // Потрібна температура зараз // Перевизначаэться в процесы перших кылькох секунд
float speedTemperature = 1; // Скорость змыни температури, в будь яку сторону (абсолютна величина)

//Input////////////////////////////////////////////////////////////////////////////////

// Time
int thisTimeSecond = 0; 
int lastTimeSecond = 59;
const int thousand = 1000; // Для того щоб выдсыювати секунди
int dexTime = 10; // Для визначення змыщення по часу
unsigned long millisecondCommon;

int hour;
int minute;
int second;
int millisecond; // timeInMilliseconds
int millisecondLast;
int millisecondSensor; // Specisl second for secsor update

int hourToEnd;
int minuteToEnd;
int secondEnd;

int millisecondOfNewCalibration; // Час пысля запуску калыбровки
int millisecondFromStartFullCalibration; // момент останнього запуску калыбровки

// Sensor
#define THERMISTORPIN A0 // Датчик температури
#define SERIESRESISTOR 304 // емкость второго резистора в цепи
#define periodMiddle 100 // Усереднювати за скільки циклів
float samples[periodMiddle]; // Масив для усереднення
float average; // Середнє значення
float lastTemperature; // Минула температура
bool firstTime = true; // Перший запис
//int numberOfSecondForTemperature = 150;
//int numberOfSecondForTemperatureSmall = 15;
//float tempertatureForEverySecond[numberOfSecondForTemperature];

// Джойстік
#define SW   14  // Пин для кнопки
#define VRX  A6 // Пин для оси Х
#define VRY  A7 // Пин для оси Y
bool pushThis = false; // Поточний стан нажаття
bool pushLast = false; // Чи нажато минулий раз на кнопку
int positionX = 512;
int positionY = 512;

// Buttons
const byte ROWS = 4; // 4 строки
const byte COLS = 4; // 4 столбца
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = 
  {2, 3, 4, 5};
  //{36,34, 32, 30}; 
byte colPins[COLS] = 
  {6, 7, 8, 9};
  //{28, 26, 24, 22}; 
Keypad keypad = Keypad(makeKeymap(keys), colPins, rowPins, ROWS, COLS);
char key = ' '; // Та що була нажата щойно
char lastKey = ' '; // Що була нажата один цикл назад, може бути пуста
char lastLongTouchKey = ' '; // Що була нажата раныше, не може бути пуста

//Output///////////////////////////////////////////////////////////////////////////////

// SendToComputer
String message = "";
int sendToComputerPeriod = 1; // Перыод выдправлення даних на компютера
bool isToSendComputer = true; // Якщо так то даны будуть посилатися на компютер

// Monitor
#define SDA   38
#define SCL   39
#define CS    40
#define RST   41 
UTFT myGLCD(ILI9486, SDA, SCL, CS, RST);
extern uint8_t SmallFont[]; // Тип тексту на екраны
extern uint8_t BigFont[];
bool isToSendMonitor = true; // Якщо так то даны будуть посилатися на монытор
String data = ""; // Даны выдправки
String calibrationIsDone = "";

//Rull/////////////////////////////////////////////////////////////////////////////////
float temperatureCoef = (float)1 / (float)60; // Скорость зміни температури
float powerSource = 0.05; // Сила ждерела напруги
float coefChanger = 10; // Коефіцієнт зміни потужності джерела живлення, зміна мощності джерела при різниці в 1 градус

//CoefSourceChanger

//ProcessRull
int timeCalibrationOfTemperature = 2000; // Час за який визначиться температура
int calibrationDifferenceTemperature = 8; // Число на скыльки градусыв буде калыбруватися система
//CoefSourceChanger

// Freezer
#define SOURCEFREEZ 11 // Пин для нагривання
float coefSourceFreez = 36;//48;//24; // Коефіцієнт потужності заморожуючого джерела
float howPowerfullWorkFreezer = 0; // Яка потужнысть роботи нагрывача

// Heater
#define SOURCEHEATER 12 // Пин для охолодження
float coefSourceHeater = 36; // Коефіцієнт потужності нагривального джерела
float howPowerfullWorkHeater= 0; // Яка потужнысть роботи заморожувача

// ButtonReaction
const int symbols = 4;
char keyMass[symbols] = {' ',' ',' ',' '};
char keyPasword[symbols] = {'#','D','*','D'};
char keyPaswordWITHslowPART[symbols] = {'*','#','A','B'};
char keyPaswordSIMPLE[symbols] = {'#','*','B','A'};


void commonSetup(){
  Serial.begin(9600); // Chanal with computer
  counter = 0; // Counter for calculate cicles
}

void inputSetup(){
  timeSetup();
  sensorSetup();
  joistSetup();
  buttonsSetup();
}
void outputSetup(){
  sendToComputerSetup();
  monitorSetup();
}
void rullSetup(){
  coefSourceChangerSetup();
  processRullSetup();
  heaterSetup();
  freezerSetup();
  buttonReactionSetup();
}


void commonUpdate(){
  counter++;
}
void inputUpdate(){
  timeUpdate();
  sensorUpdate();
  joistUpdate();
  buttonsUpdate();
}
void outputUpdate(){
  sendToComputerUpdate();
  monitorUpdate();
}
void rullUpdate(){
  coefSourceChangerUpdate();
  processRullUpdate();
  heaterUpdate();
  freezerUpdate();
  buttonReactionUpdate();
}



void setup() {
  commonSetup();
  inputSetup();
  outputSetup();
  rullSetup();
  delay(1000);
}

void loop() {
  commonUpdate();
  inputUpdate();
  outputUpdate();
  rullUpdate();
}
