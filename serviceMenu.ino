//Main Service Menu
void serviceMenu()
{
  if(back.pressed()) {states = exitAny;}

  switch(serviceSwitch)
  {
    case 0:
      delay(500);
      ledWrite("5ERU1CE.", 'L');
      serialSend(9876);
      serviceSwitch = 1;
      break;

    case 1:
      lcdWrite(0, 0, F("Service Mode:"), 'C');
      lcdWrite(0, 1, F("Enter = Save Changes"));
      lcdWrite(0, 2, F("Up/Down = Select"), 'C');
      lcdWrite(0, 3, F("Left/Right = Change"), 'L');
      delay(2000);
      serviceSwitch = 2;
      break;

    case 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Scroll through"), 'C');
      lcdWrite(0, 2, F("Selections."), 'C');
      lcdWrite(0, 3, deadspace20);
      delay(2000);
      serviceSwitch = 3;
      break;

    case 3:
      flashButton(upLED, enterLED, downLED, backLED);
      //Reset Menu Switches Upon Backing Out of a Menu:
      if(cellSwitch > 0) {cellSwitch = 0;}
      if(coloursMenuSwitch > 0) {coloursMenuSwitch = 0;}
      if(playerSwitch > 1) {playerSwitch = 1;}
      if(timerMenuSwitch > 0) {timerMenuSwitch = 0;}
      if(thresholdMenuSwitch > 0) {thresholdMenuSwitch = 0;}
      if(incrementMenuSwitch > 0) {incrementMenuSwitch = 0;}
      if(brightnessMenuSwitch >0) {brightnessMenuSwitch = 0;}
      if(lcdBrightnessMenuSwitch > 0) {lcdBrightnessMenuSwitch = 0;}
      if(playerDisplayBrightnessMenuSwitch) {playerDisplayBrightnessMenuSwitch = 0;}
      //End Menu Resets
      
      if(sm >= 1 && sm <= 4)
      {
        ledWrite("PAgE.  1", 'C');
        lcdWrite(1, 0, F("Player Colours"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1, 1, F("Game Timer"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1, 2, F("Threshold Rotations"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1, 3, F("Beacons Setup"), 'L', 19);  //19 Characters because of selection arrow.
      }
      else if(sm >= 5 && sm <= 8)
      {
        ledWrite("PAgE.  2", 'C');
        lcdWrite(1, 0, F("Increment Num LEDs"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1, 1, F("Idle Animation"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1 ,2, F("Brightness Menu"), 'L', 19);  //19 Characters because of selection arrow.
        lcdWrite(1, 3, F("Test Menu"), 'L', 19);  //19 Characters because of selection arrow.
      }
      else if(sm >= 9 && sm <= 12)
      {
        ledWrite("PAgE.  3", 'C');
         lcdWrite(1, 0, F("LCD Brightness"), 'L', 19);  //19 Characters because of selection arrow.
         lcdWrite(1, 1, F("Plyr Dsp Brightness"), 'L', 19);  //19 Characters because of selection arrow.
         lcdWrite(0, 2, deadspace20);
         lcdWrite(0, 3, deadspace20);
      }

      if(up.pressed())
      {
        sm --;
        if(sm <= 0)
        {
          sm = 10;
        }
      }
      else if(down.pressed())
      {
        sm ++;
        if(sm >= 11)
        {
          sm = 1;
        }
      }
      
      switch(sm)
      {
        case 0: sm = 1; break;
        case 1: arrow(0); break;
        case 2: arrow(1); break;
        case 3: arrow(2); break;
        case 4: arrow(3); break;
        case 5: arrow(0); break;
        case 6: arrow(1); break;
        case 7: arrow(2); break;
        case 8: arrow(3); break;
        case 9: arrow(0); break;
        case 10: arrow(1); break;
        default: sm = 1; break;
      }
      if(enter.pressed())
      {
        stopFlashAll();
        switch(sm)
        {
          case 1: states = coloursMenuCase; break;
          case 2: states = timerMenuCase; break;
          case 3: states = thresholdMenuCase; break;
          case 4: states = beaconsMenuCase; break;
          case 5: states = incrementMenuCase; break;
          case 6: states = idleMenuCase; break;
          case 7: states = brightnessMenuCase; break;
          case 8: states = testMenuCase; break;
          case 9: states = lcdBrightnessCase; break;
          case 10: states = playerDisplayBrightnessCase; break;
        }
      }
      break;

    default:
      serviceSwitch = 0;
      break;
  }
}
//End Main Service Menu




//Timer Menu:
void timerMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  
  switch(timerMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      timerMenuSwitch = 1;
      break;

    case 1:  //Menu Instructions:
      ledWrite("t1NER", 'C');
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Game Timer"), 'C');
      lcdWrite(0, 3, deadspace20);
      delay(2000);
      timerMenuSwitch = 2;
      break;

    case 2:  //Main Settings Menu Screen
      lcdWrite(0, 0, F("Enter to Save Value"), 'L');
      lcdWrite(0, 1, F("Back to Exit"), 'C');
      lcdWrite(0, 2, F("Up/Down to Change"), 'C');

      //Button LED Handler:
      if(timer != 5 && timer != 90)
      {
        flashButton(upLED, enterLED, downLED, backLED);
      }
      else if(timer == 90)
      {
        stopFlashSingle(upLED);
        flashButton(enterLED, downLED, backLED);
      }
      else if(timer == 5)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      //End Button LED Handler

      if(up.pressed())
      {
        timer += 5;
        if(timer >= 91)
        {
          timer = 90;
        }
      }
      else if(down.pressed())
      {
        timer -= 5;
        if(timer <= 5)
        {
          timer = 5;
        }
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        serialSend(timer + 100);
        timerMenuSwitch = 3;
      }
      
      lcdWrite(0, 3, "Timer = " + String(timer) + " Seconds  ", 'C');
      break;

    case 3:  //Save and Return:
      saveVal = 1;
      states = saveCase;
      break;

    default:
      timerMenuSwitch = 0;
      break;
  }
}
//End Timer Menu




//Threshold Menu:
void thresholdMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  
  switch(thresholdMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      thresholdMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("thRE5hLd");
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Amount Truns on Bike"));
      lcdWrite(0, 2, F("to Light up Lines on"));
      lcdWrite(0, 3, F("Displays"), 'C');
      delay(2000);
      thresholdMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      thresholdMenuSwitch = 3;
      break;

    case 3:  //Main Settings Menu Screen:
      //Buttons LEDs Handler:
      if(threshold != 1 && threshold != 5)
      {
        flashButton(upLED, downLED, enterLED, backLED);
      }
      else if(threshold == 1)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      else if(threshold == 5)
      {
        stopFlashSingle(upLED);
        flashButton(downLED, enterLED, backLED);
      }
      //End Buttons LED Handler
      
      lcdWrite(0, 0, F("Up/Down = +/-"), 'C');
      lcdWrite(0, 1, F("Turns per Increment"), 'L');
      lcdWrite(0, 2, F("Variable 1 - 5"), 'C');

      if(up.pressed())
      {
        threshold ++;
        if(threshold >= 6)
        {
          threshold = 5;
        }
      }
      else if(down.pressed())
      {
        threshold --;
        if(threshold <= 0)
        {
          threshold = 1;
        }
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        serialSend(threshold + 560);
        thresholdMenuSwitch = 4;
      }
      
      lcdWrite(0, 3, "Threshold = " + String(threshold) + " Turns", 'L');
      break;

    case 4:  //Save
      saveVal = 7;
      states = saveCase;
      break;

    default:
      thresholdMenuSwitch = 0;
      break;
  }
}
//End Threshold Menu




//Beacons Menu:
void beaconsMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  ledWrite("bEAC0N5", 'L');
  lcdWrite(0, 0, deadspace20);
  lcdWrite(0, 1, F("Nothing Here Yet"), 'C');
  lcdWrite(0, 2, F("Press Back to Exit"), 'C');
  lcdWrite(0, 3, deadspace20);
}
//End Beacons Menu




//Increment Menu:
void incrementMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  
  switch(incrementMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      incrementMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("1NC. LEd5");
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Amount of LEDs"), 'C');
      lcdWrite(0, 2, F("Lit per Threshold."), 'C');
      lcdWrite(0, 3, F("---Turns on Bikes---"));
      delay(2000);
      incrementMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      incrementMenuSwitch = 3;
      break;

    case 3:  //Main Settings Menu Screen:
      //Buttons LEDs Handler:
      if(increment != 1 && increment != 5)
      {
        flashButton(upLED, downLED, enterLED, backLED);
      }
      else if(increment == 1)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      else if(increment == 5)
      {
        stopFlashSingle(upLED);
        flashButton(downLED, enterLED, backLED);
      }
      //End Buttons LED Handler
      
      lcdWrite(0, 0, F("Up/Down = +/-"), 'C');
      lcdWrite(0, 1, F("Increments per Turn:"));
      lcdWrite(0, 2, F("Variable 1 - 5"), 'C');

      if(up.pressed())
      {
        increment ++;
        if(increment >= 6)
        {
          increment = 5;
        }
      }
      else if(down.pressed())
      {
        increment --;
        if(increment <= 0)
        {
          increment = 1;
        }
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        serialSend(increment + 200);
        incrementMenuSwitch = 4;
      }
      
      lcdWrite(0, 3, "Increment = " + String(increment) + " LEDs", 'C');
      break;

    case 4:  //Save
      saveVal = 2;
      states = saveCase;
      break;

    default:
      incrementMenuSwitch = 0;
      break;
  }
}
//End Increment Menu




//Idle Menu:
void idleMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  ledWrite("1dLE.5tUP");
  lcdWrite(0, 0, deadspace20);
  lcdWrite(0, 1, F("Nothing Here Yet"), 'C');
  lcdWrite(0, 2, F("Press Back to Exit"), 'C');
  lcdWrite(0, 3, deadspace20);
}
//End Idle Menu




//Brightness Menu:
void brightnessMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }
  
  switch(brightnessMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      brightnessMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("LED. bRht", 'L');
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Brightness of"), 'C');
      lcdWrite(0, 2, F("Matrix Display LEDs"), 'L');
      lcdWrite(0, 3, deadspace20);
      delay(2000);
      brightnessMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      brightnessMenuSwitch = 3;
      break;

    case 3:  //Main Settings Menu Screen:
      //Buttons LEDs Handler:
      if(brightness != 10 && brightness != 200)
      {
        flashButton(upLED, downLED, enterLED, backLED);
      }
      else if(brightness == 10)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      else if(brightness == 200)
      {
        stopFlashSingle(upLED);
        flashButton(downLED, enterLED, backLED);
      }
      //End Buttons LED Handler
      
      lcdWrite(0, 0, F("Up/Down = +/-"), 'C');
      lcdWrite(0, 1, F("Matrix Brightness:"), 'C');
      lcdWrite(0, 2, F("Variable 10 - 200"), 'C');

      if(up.pressed())
      {
        brightness ++;
        if(brightness >= 200)
        {
          brightness = 200;
        }
        serialSend(brightness + 300);
      }
      else if(down.pressed())
      {
        brightness --;
        if(brightness <= 10)
        {
          brightness = 10;
        }
        serialSend(brightness + 300);
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        brightnessMenuSwitch = 4;
      }
      
      lcdWrite(0, 3, "Brightness = " + String(brightness) + "", 'C');
      break;

    case 4:
      saveVal = 3;
      states = saveCase;
      break;

    default:
      brightnessMenuSwitch = 0;
      break;
  }
}
//End Brightness Menu




//Test Menu:
void testMenu()
{
  if(back.pressed())
  {
    serviceSwitch = 3;
    states = serviceCase;
  }
  ledWrite("tE5t", 'C');
  lcdWrite(0, 0, deadspace20);
  lcdWrite(0, 1, F("Nothing Here Yet"), 'C');
  lcdWrite(0, 2, F("Press Back to Exit"), 'C');
  lcdWrite(0, 3, deadspace20);
}
//End Test Menu




//LCD Brightness Menu:
void lcdBrightness()
{
  analogWrite(backlight, BLmap);
  
  if(back.pressed())
  {
    serviceSwitch = 3;
    stopFlashAll();
    states = serviceCase;
  }

  switch(lcdBrightnessMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      lcdBrightnessMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("LCD. bRht", 'L');
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Brightness of"), 'C');
      lcdWrite(0, 2, F("LCD Display"), 'C');
      lcdWrite(0, 3, deadspace20);
      delay(2000);
      lcdBrightnessMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      lcdBrightnessMenuSwitch = 3;
      break;

    case 3:  //Main Settings Menu Screen:
      //Buttons LEDs Handler:
      if(BL != 1 && BL != 100)
      {
        flashButton(upLED, downLED, enterLED, backLED);
      }
      else if(BL == 1)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      else if(BL == 100)
      {
        stopFlashSingle(upLED);
        flashButton(downLED, enterLED, backLED);
      }
      //End Buttons LED Handler
      
      lcdWrite(0, 0, F("Up/Down = +/-"), 'C');
      lcdWrite(0, 1, F("LCD Brightness:"), 'C');
      lcdWrite(0, 2, F("Variable 1 - 100%"), 'C');

      if(up.pressed())
      {
        BL ++;
        if(BL >= 100)
        {
          BL = 100;
        }
      }
      else if(down.pressed())
      {
        BL --;
        if(BL <= 1)
        {
          BL = 1;
        }
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        lcdBrightnessMenuSwitch = 4;
      }
      
      lcdWrite(0, 3, "LCD Brightness: " + String(BL) + "%", 'L');
      break;

    case 4:
      saveVal = 8;
      states = saveCase;
      break;

    default:
      lcdBrightnessMenuSwitch = 0;
      break;
  }
}
//End LCD Brightness Menu




//PlayerDisplay Brightness Menu:
void playerDisplayBrightness()
{
  if(back.pressed()) {playerDisplayBrightnessMenuSwitch = 5;}

  switch(playerDisplayBrightnessMenuSwitch)
  {
    case 0:  //Soft Enter:
      delay(500);
      playerDisplayBrightnessMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("PLR. bRht", 'L');
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Brightness of"), 'C');
      lcdWrite(0, 2, F("Player Display"), 'C');
      lcdWrite(0, 3, deadspace20);
      delay(2000);
      playerDisplayBrightnessMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Press Up/Down Key to"));
      lcdWrite(0, 1, F("Increment/Decrement"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      playerDisplayBrightnessMenuSwitch = 3;
      break;

    case 3:  //Main Settings Menu Screen:
      //Buttons LEDs Handler:
      if(pBrightness != 10 && pBrightness != 100)
      {
        flashButton(upLED, downLED, enterLED, backLED);
      }
      else if(pBrightness == 10)
      {
        stopFlashSingle(downLED);
        flashButton(upLED, enterLED, backLED);
      }
      else if(pBrightness == 100)
      {
        stopFlashSingle(upLED);
        flashButton(downLED, enterLED, backLED);
      }
      //End Buttons LED Handler

      playerFill(p1Display, 255, 255, 255);
      playerFill(p2Display, 255, 255, 255);
      
      lcdWrite(0, 0, F("Up/Down = +/-"), 'C');
      lcdWrite(0, 1, F("Plyr Dsp Brightness:"));
      lcdWrite(0, 2, F("Variable 10 - 100%"), 'C');

      if(up.pressed())
      {
        pBrightness ++;
        if(pBrightness >= 100)
        {
          pBrightness = 100;
        }
      }
      else if(down.pressed())
      {
        pBrightness --;
        if(pBrightness <= 10)
        {
          pBrightness = 10;
        }
      }
      else if(enter.pressed())
      {
        stopFlashAll();
        playerDisplayBrightnessMenuSwitch = 4;
      }
      
      lcdWrite(0, 3, "PD Brightness: " + String(pBrightness) + "%", 'L');
      break;

    case 4:  //Save:
      playerClear(p1Display);
      playerClear(p2Display);
      saveVal = 9;
      states = saveCase;
      break;

    case 5:  //Exit Out:
      playerClear(p1Display);
      playerClear(p2Display);
      serviceSwitch = 3;
      stopFlashAll();
      states = serviceCase;
      break;

    default:
      playerDisplayBrightnessMenuSwitch = 0;
      break;
  }
}
//End Player Display Brightness Menu
