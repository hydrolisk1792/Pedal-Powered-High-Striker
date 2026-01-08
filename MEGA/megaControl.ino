#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LedControl.h>
#include <Adafruit_NeoPixel.h>

#include "src/Button.h"

#define bootstrap 16
#define backlight 13
#define upLED 51
#define downLED 47
#define leftLED 49
#define rightLED 50
#define backLED 46
#define enterLED 48
#define startLED 52
#define resetLED 53
#define p1Pin 10
#define p2Pin 12
//#define reserved 14  //Unused pin on "LED" Connector
#define pixels 6

Button up(20);
Button down(21);
Button left(22);
Button right(23);
Button back(24);
Button enter(25);

//System Objects:
const int lcdRs = 31, lcdEn = 29, lcdD4 = 27, lcdD5 = 30, lcdD6 = 28, lcdD7 = 26;
LiquidCrystal lcd(lcdRs, lcdEn, lcdD4, lcdD5, lcdD6, lcdD7);
LedControl led7seg = LedControl(4, 6, 8, 1);
Adafruit_NeoPixel p1Display(pixels, p1Pin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel p2Display(pixels, p2Pin, NEO_GRB + NEO_KHZ800);
//End System Objects

//Serial Variables:
int serialData = 0;  //Integer to Hold Incoming Data
const char startDelimiter = '<';  //Start of Serial String
const char endDelimiter = '>';  //End of Serial String
//End Serial Variables

//System Switches:
byte idleSwitch = 0;  //Idle Mode Switch
byte bootupSwitch = 0;  //Boot Up State Machine
byte serviceSwitch = 0;  //Main Service Switch
byte sm = 1;  //Used for Selections
byte coloursMenuSwitch = 0;  //Colours Menu Switch
byte playerSwitch = 1;  //Select Player Switch
byte cArrow = 1;  //Select Colour Switch
byte timerMenuSwitch = 0;  //Timer Menu Switch
byte thresholdMenuSwitch = 0;  //Threshold Menu Switch
byte incrementMenuSwitch = 0;  //Increment Menu Switch
byte brightnessMenuSwitch = 0;  //Brightness Menu Switch
byte lcdBrightnessMenuSwitch = 0;  //LCD Brightness Menu Switch
byte playerDisplayBrightnessMenuSwitch = 0;  //Player Display Brightness Menu Switch
byte saveVal = 0;  //Save Switch
byte cellSwitch = 0;  //Save Handler Switch
byte gameState = 0;  //Game State Switch
byte ani = 0;  //For LED Animate
//End System Switches

//System Integers & Bytes:
int BL;  //integer to Hold Brightness of LCD
int BLmap = 0;  //Integer to Hold Brightness Map Data of LCD
int pBrightness;  //Integer to Hold Player Display Brightness
int pBrightnessMap = 0;  //Integer to Hold Player Brightness Map Data
byte timer = 0;  //Byte to Hold Timer Value to Send
byte threshold = 0;  //Byte to Hold Threshold Value to Send
byte increment = 0;  //Byte to Hold the Increment Value to Send
byte brightness = 0;  //Byte to Hold Brightness Value to Send
byte countdown = 0;  //For Visual Timer from Main
byte p1Points = 0;  //Player 1 Points
byte p2Points = 0;  //Player 2 Points
byte p1R;  //Player 1 Red Setting
byte p1G;  //Player 1 Green Setting
byte p1B;  //Player 1 Blue Setting
byte p2R;  //Player 2 Red Setting
byte p2G;  //Player 2 Green Setting
byte p2B;  //Player 2 Blue Setting
byte umR;  //Upper Matrix Red Setting
byte umG;  //Upper Matrix Green Setting
byte umB;  //Upper Matrix Blue Setting
//End System Integers & Bytes

//System Strings:
String deadspace20 = "                    ";
//End System Strings

//FSM:
enum states
{
  bootup,
  clearAll,
  idle,
  gameCase,
  serviceCase,
  coloursMenuCase,
  timerMenuCase,
  thresholdMenuCase,
  beaconsMenuCase,
  incrementMenuCase,
  idleMenuCase,
  brightnessMenuCase,
  testMenuCase,
  lcdBrightnessCase,
  playerDisplayBrightnessCase,
  saveCase,
  exitAny
}
states = bootup;
//End FSM

//System Prototypes:
void boot();
void processData(const long n);
void processInput();
void serialSend(const int x);
String makeSpaces(byte count);
void lcdWrite(const byte col, const byte line, const String & text, char just = 'A', const byte lineWidth = 20);
void lcdWrite(const byte col, const byte line, const __FlashStringHelper * textF, char just = 'A', const byte lineWidth = 20);
void lcdWrite(const byte col, const byte line, const char * text, char just = 'A', const byte lineWidth = 20);
void specCharHandler(byte col, byte row, long a, long b, long c, long d, long e, long f, long g, long h);
void specChar(byte col, byte row, byte select);
void arrow(byte x);
void led7segWrite(byte digit, int character, boolean dp);
void segment(byte digit);
void ledWrite(byte start, const String & text, char just, byte fieldWidth);
void ledWrite(const String & text, char just = 'A');
void ledWrite(byte start, const String & text, char just = 'A');
void serviceMenu();
void coloursMenu();
void colourChange(byte & r, byte & g, byte & b, int ri, int gi, int bi);
void colourArrow();
void timerMenu();
void thresholdMenu();
void beaconsMenu();
void incrementMenu();
void idleMenu();
void brightnessMenu();
void testMenu();
void save();
void saveHandler(byte cell, byte var);
void ledSaveHandler(byte cell1, byte cell2, byte cell3, byte var1, byte var2, byte var3);
void idleMode();
void gameStatus();
void Clear();
void flashButton(int a, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0, int h = 0);
void stopFlashAll(void);
void stopFlashSingle(int a, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0, int h = 0);
void playerFill(Adafruit_NeoPixel & p, byte r, byte g, byte b);
void playerClear(Adafruit_NeoPixel & p);
//End System Prototypes



//System Setup:
void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial1.begin(9600);
  delay(1000);
  
  pinMode(upLED, OUTPUT);
  pinMode(downLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(backLED, OUTPUT);
  pinMode(enterLED, OUTPUT);
  pinMode(startLED, OUTPUT);
  pinMode(resetLED, OUTPUT);
  pinMode(bootstrap, OUTPUT);
  digitalWrite(bootstrap, HIGH);

  //Setup LED Display:
  led7seg.shutdown(0, false);
  led7seg.setIntensity(0, 1);
  led7seg.setScanLimit(0, 8);
  led7seg.clearDisplay(0);
  //End LED Display

  //Load from Rom:
  timer = EEPROM.read(1);
  increment = EEPROM.read(2);
  brightness = EEPROM.read(3);
  threshold = EEPROM.read(4);
  BL = EEPROM.read(5);
  pBrightness = EEPROM.read(6);
  p1R = EEPROM.read(10);
  p1G = EEPROM.read(11);
  p1B = EEPROM.read(12);
  p2R = EEPROM.read(13);
  p2G = EEPROM.read(14);
  p2B = EEPROM.read(15);
  umR = EEPROM.read(16);
  umG = EEPROM.read(17);
  umB = EEPROM.read(18);
  //End Load from Rom

  //Setup Backlight Pin Settings:
  pinMode(backlight, OUTPUT);
  analogWrite(backlight, BL * 2.55);
  //End Backlight Pin
  
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.clear();

  p1Display.begin();
  p1Display.clear();
  p1Display.setBrightness(pBrightnessMap);
  p2Display.begin();
  p2Display.clear();
  p2Display.setBrightness(pBrightnessMap);
}
//End System Setup




//System Loop:
void loop()
{
  if(Serial1.available()) {processInput();}  //Listen for Incoming Data

  BLmap = map(BL, 0, 100, 0, 255);
  pBrightnessMap = map(pBrightness, 0, 100, 0, 255);
  
  switch(states)
  {
    case bootup: boot(); break;
    case clearAll: Clear(); break;
    case idle: idleMode(); break;
    case gameCase: gameStatus(); break;
    case serviceCase: serviceMenu(); break;
    case coloursMenuCase: coloursMenu(); break;
    case timerMenuCase: timerMenu(); break;
    case thresholdMenuCase: thresholdMenu(); break;
    case beaconsMenuCase: beaconsMenu(); break;
    case incrementMenuCase: incrementMenu(); break;
    case idleMenuCase: idleMenu(); break;
    case brightnessMenuCase: brightnessMenu(); break;
    case testMenuCase: testMenu(); break;
    case lcdBrightnessCase: lcdBrightness(); break;
    case playerDisplayBrightnessCase: playerDisplayBrightness(); break;
    case saveCase: save(); break;
    case exitAny: returning(); break;
    default: states = clearAll; break;
  }
}
//End System Loop
