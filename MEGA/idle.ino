//Idle Mode
void idleMode()
{
  static unsigned long idleMillis = millis();

  //Buttons LEDs Handler:
  if(idleSwitch != 0)
  {
    stopFlashSingle(leftLED, rightLED, backLED, resetLED);
    flashButton(startLED, enterLED, upLED, downLED);
  }
  else if(idleSwitch == 0)
  {
    stopFlashSingle(upLED, leftLED, rightLED, backLED, resetLED);
    flashButton(startLED, enterLED, downLED);
  }
  //End Buttons LEDs Handler

  ledWrite(1, "-1dLE-", 'L', 6);
  segment(0);
  segment(7);

  if(enter.pressed())
  {
    stopFlashAll();
    states = serviceCase;
  }
  
  if(down.pressed())
  {
    idleSwitch ++;
    if(idleSwitch >= 4)
    {
      idleSwitch = 0;
    }
  }
  else if(up.pressed())
  {
    idleSwitch --;
    if(idleSwitch <= 0)
    {
      idleSwitch = 0;
    }
  }
  
  if(millis() - idleMillis > 2500)
  {
    idleMillis = millis();
    idleSwitch ++;
    if(idleSwitch >= 4)
    {
      idleSwitch = 0;
    }
  }
  
  switch(idleSwitch)
  {
    case 0:
      lcdWrite(0, 0, "Game Timer = " + String(timer) + " secs", 'L');
      if(increment == 1) {lcdWrite(0, 1, "Increment = " + String(increment) + " Line", 'L');}  //No "S"
      else {lcdWrite(0, 1, "Increment = " + String(increment) + " Lines", 'L');}  //Add "S"
      if(threshold == 1) {lcdWrite(0, 2, "Threshold = " + String(threshold) + " Turn", 'L');}  //No "S"
      else {lcdWrite(0, 2, "Threshold = " + String(threshold) + " Turns", 'L');}  //Add "S"
      lcdWrite(0, 3, deadspace20);
      break;

    case 1:
      lcdWrite(0, 0, F("Player 1 RGB Colour:"));
      lcdWrite(0, 1, "R: " + String(p1R) + " G: " + String(p1G) + " B: " + String(p1B), 'C');
      lcdWrite(0, 2, F("Player 2 RGB Colour:"));
      lcdWrite(0, 3, "R: " + String(p2R) + " G: " + String(p2G) + " B: " + String(p2B), 'C');
      break;

    case 2:
      lcdWrite(0, 0, deadspace20);
      lcdWrite(0, 1, F("Top Disp RGB Colour:"));
      lcdWrite(0, 2, "R: " + String(umR) + " G: " + String(umG) + " B: " + String(umB), 'C');
      lcdWrite(0, 3, deadspace20);
      break;

    case 3:
      lcdWrite(0, 0, F("Enter = Service Mode"));
      lcdWrite(0, 1, F("Start = Start Game"), 'C');
      lcdWrite(0, 2, F("Reset = Cancel Game"), 'L');
      lcdWrite(0, 3, F("U/D = Scroll Screen"), 'L');
      break;
  }
}
//End Idle Mode
