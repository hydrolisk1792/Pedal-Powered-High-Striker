#include <Adafruit_NeoMatrix.h>
#include <HardwareSerial.h>
#include "src/Button.h"

//Serial Pins:
#define tx 17
#define rx 16
//End Serial Pins

//Matrix Defines:
#define p1MatrixPin 12
#define p2MatrixPin 13
#define upperMatrixPin 14
#define matrixWidth 224
#define matrixHeight 8
#define upperWidth 32
//End Matrix Defines

//Define Hold Pins:
#define bootstrap 19
//End Define Hold Pins

//Buttons:
Button reset(26);
Button start(27);
//End Buttons

//System Objects:
Adafruit_NeoMatrix p1Matrix  //Left Tower
(
  matrixWidth,
  matrixHeight,
  p1MatrixPin,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800
);

Adafruit_NeoMatrix p2Matrix  //Right Tower
(
  matrixWidth,
  matrixHeight,
  p2MatrixPin,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800
);

Adafruit_NeoMatrix upperMatrix  //Timer Display
(
  upperWidth,
  matrixHeight,
  upperMatrixPin,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800
);
//End System Objects

//System Structures:
struct opto1Struct
{
  const uint8_t PIN;
  uint32_t numBroken1;
  boolean broken1;
};

struct opto2Struct
{
  const uint8_t PIN;
  uint32_t numBroken2;
  boolean broken2;
};

opto1Struct opto1 = {18, 0, false};
opto2Struct opto2 = {5, 0, false};
//End System Structures

//Serial Variables:
int serialData = 0;
const char startDelimiter = '<';
const char endDelimiter = '>';
//End Serial Variables

//System Switches:
byte idleAniSwitch = 0;  //Used for Idle Animation Switching
byte gameStartSwitch = 0;  //Game Start Switch
byte gamePlaySwitch = 0;  //Game Play Switch
byte gameOverSwitch = 0;  //Game Over Switch
//End System Switches

//System Integers & Bytes:
int starting = upperMatrix.width();  //Width of Upper Matrix for Scroll Function
int charPixels = 6;  //Width of Characters for Scroll Function
int p1Points = 0;  //Player 1 Points
int p2Points = 0;  //Player 2 Points
byte increment = 0;  //How Many Lines to Fill
byte brightness = 10;  //Brightness of LED Matrix
byte threshold = 1;  //Ammount of Rotations it Takes to Count
byte threshTemp = 0;  //Temporary Threshold
byte p1R;  //Player 1 Red Setting
byte p1G;  //Player 1 Green Setting
byte p1B;  //Player 1 Blue Setting
byte p2R;  //Player 2 Red Setting
byte p2G;  //Player 2 Green Setting
byte p2B;  //Player 2 Blue Setting
byte umR;  //Upper Matrix Red Setting
byte umG;  //Upper Matrix Green Setting
byte umB;  //Upper Matrix Blue Setting
byte flashTimes = 0;  //Number of Times to Flash the Winner
//End System Integers & Bytes

//System Timers:
unsigned long prevTimer = millis();  //Timer Previous Time
const int intervalTimer = 1000;  //1 Second Clock Pulse for Timer
unsigned long setTimer;
unsigned long timer = 0;
//End System Timers

//System Flags:
boolean bootstrapState = HIGH;  //Boot Strap Flag
boolean flashWinnerFlag = false;
//End System Flags

//FSM:
enum states
{
  bootup,
  clearAll,
  idle,
  serviceCase,
  gameStartCase,
  gamePlayCase,
  endGameCase,
  exitAny
}
states = bootup;
//End FSM

//System Prototypes:
void IRAM_ATTR isr1();
void IRAM_ATTR isr2();
void processData(const long n);
void processInput();
void serialSend(const int x);
void ledWrite(const char p, byte c, byte d, String text, byte r, byte g, byte b);
void scrollText(String text, int t = 25);
void serviceMode();
void brightnessFunc();
void idleAni();
void snowSparkle();
void fillBoth(byte r, byte g, byte b);
void fillBar();
void boarder();
void gameStartHandler();
void gamePlayHandler();
//End System Prototypes




//System Setup:
void setup()
{
  Serial.begin(9600);
  delay(1000);

  //Opto:
  pinMode(opto1.PIN, INPUT);
  pinMode(opto2.PIN, INPUT);
  attachInterrupt(opto1.PIN, isr1, CHANGE);  //Change?  FALLING
  attachInterrupt(opto2.PIN, isr2, CHANGE);  //Change?  FALLING
  //End Opto

  pinMode(bootstrap, INPUT_PULLUP);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  Serial2.begin(9600, SERIAL_8N1, rx, tx);
  delay(1000);

  //Setup Matrices:
  p1Matrix.begin();
  p2Matrix.begin();
  upperMatrix.begin();
  p1Matrix.setTextWrap(false);
  p2Matrix.setTextWrap(false);
  upperMatrix.setTextWrap(false);
  p1Matrix.setBrightness(brightness);
  p2Matrix.setBrightness(brightness);
  upperMatrix.setBrightness(brightness);
  p1Matrix.setTextSize(1);
  p2Matrix.setTextSize(1);
  upperMatrix.setTextSize(1);
  p1Matrix.clear();
  p1Matrix.show();
  p2Matrix.clear();
  p2Matrix.show();
  upperMatrix.clear();
  upperMatrix.show();
  //End Setup Matrices

  //Test:
  p1Matrix.fillScreen(0);
  p1Matrix.setTextColor(p1Matrix.Color(255, 0, 0));
  p1Matrix.clear();
  p1Matrix.setCursor(0, 0);
  p1Matrix.print("This is a test Hello World 1234567890");
  p1Matrix.show();

  p2Matrix.fillScreen(0);
  p2Matrix.setTextColor(p1Matrix.Color(255, 0, 0));
  p2Matrix.clear();
  p2Matrix.setCursor(0, 0);
  p2Matrix.print("This is a test Hello World 1234567890");
  p2Matrix.show();

  upperMatrix.fillScreen(0);
  upperMatrix.setTextColor(p1Matrix.Color(255, 0, 0));
  upperMatrix.clear();
  upperMatrix.setCursor(0, 0);
  upperMatrix.print("01234");
  upperMatrix.show();
  //End Test
}
//End System Setup




//System Loop:
void loop()
{
  bootstrapState = digitalRead(bootstrap);
  
  if(Serial2.available()) {processInput();}  //Listen for Incoming Data
  
  switch(states)
  {
    case bootup:
      brightnessFunc();
      scrollText("System Booting.....");
      if(!bootstrapState) {states = idle;}
      break;
      
    case clearAll:
      serialSend(9998);
      states = idle;
      break;

    case idle:
      idleAni();
      scrollText("Pedal Power High Striker");
      if(start.pressed()) {states = gameStartCase;}
      break;

    case serviceCase: serviceMode(); break;
    case gameStartCase: gameStartHandler(); break;
    case gamePlayCase: gamePlayHandler(); break;
    case endGameCase: gameOverHandler(); break;
    case exitAny: returning(); break;
  }
}
//End System Loop
