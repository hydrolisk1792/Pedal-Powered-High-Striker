//Returning:
void returning()
{
  stopFlashAll();
  ledWrite("REtURN", 'C');
  serialSend(9877);
  if(serviceSwitch > 0) {serviceSwitch = 0;}
  if(sm > 1) {sm = 1;}
  if(coloursMenuSwitch > 0) {coloursMenuSwitch = 0;}
  if(playerSwitch > 1) {playerSwitch = 1;}
  if(timerMenuSwitch > 0) {timerMenuSwitch = 0;}
  if(thresholdMenuSwitch > 0) {thresholdMenuSwitch = 0;}
  if(incrementMenuSwitch > 0) {incrementMenuSwitch = 0;}
  if(brightnessMenuSwitch >0) {brightnessMenuSwitch = 0;}
  if(lcdBrightnessMenuSwitch > 0) {lcdBrightnessMenuSwitch = 0;}
  if(playerDisplayBrightnessMenuSwitch > 0) {playerDisplayBrightnessMenuSwitch = 0;}
  if(saveVal > 0) {saveVal = 0;}
  if(cellSwitch > 0) {cellSwitch = 0;}
  lcdWrite(0, 0, deadspace20);
  lcdWrite(0, 1, F("Returning to Normal "), 'L');
  lcdWrite(0, 2, F("Operation Mode"), 'C');
  lcdWrite(0, 3, deadspace20);
  delay(1500);
  states = clearAll;
}
//End Returning
