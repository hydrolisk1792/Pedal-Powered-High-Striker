//Colours Menu:
void coloursMenu()
{
  switch(coloursMenuSwitch)
  {
    case 0:
      delay(500);
      coloursMenuSwitch = 1;
      break;

    case 1:  //Instructions 1:
      ledWrite("C0L0UR", 'C');
      lcdWrite(0, 0, F("This Changes the"), 'C');
      lcdWrite(0, 1, F("Colour of Player 1,"), 'L');
      lcdWrite(0, 2, F("Player 2, and"), 'C');
      lcdWrite(0, 3, F("Upper Display"), 'C');
      delay(2000);
      coloursMenuSwitch = 2;
      break;

    case 2:  //Instructions 2:
      lcdWrite(0, 0, F("Up/Down = + or -"), 'C');
      lcdWrite(0, 1, F("Left/Right = Select"), 'L');
      lcdWrite(0, 2, F("Enter to Save Value"), 'L');
      lcdWrite(0, 3, F("Back to Exit"), 'C');
      delay(2000);
      coloursMenuSwitch = 3;
      break;

    case 3:  //Main Menu Functions:
      //Button LED Handler:
      if(playerSwitch != 1 && playerSwitch != 3)
      {
        stopFlashSingle(upLED, downLED);
        flashButton(leftLED, enterLED, rightLED, backLED);
      }
      else if(playerSwitch == 1)
      {
        stopFlashSingle(leftLED, upLED, downLED);
        flashButton(enterLED, rightLED, backLED);
      }
      else if(playerSwitch == 3)
      {
        stopFlashSingle(rightLED, upLED, downLED);
        flashButton(leftLED, enterLED, backLED);
      }
      //End Button LED Handler

      ledWrite("C0L0UR", 'C');
      
      if(cellSwitch > 0) {cellSwitch = 0;}  //Reset Save Switch
      
      if(back.pressed())
      {
        serviceSwitch = 3;
        stopFlashAll();
        states = serviceCase;
      }
      
      lcdWrite(0, 0, F("L/R = Player Select"), 'L');
      lcdWrite(0, 1, F("Entr = Select Player"));
      lcdWrite(0, 2, deadspace20);

      if(left.pressed())
      {
        playerSwitch --;
        if(playerSwitch <= 1)
        {
          playerSwitch = 1;
        }
      }
      else if(right.pressed())
      {
        playerSwitch ++;
        if(playerSwitch >= 4)
        {
          playerSwitch = 3;
        }
      }
      
      switch(playerSwitch)
      {
        case 0: break;
        
        case 1:
          lcdWrite(0, 3, F("Player 1 Colour"), 'C');
          if(enter.pressed())
          {
            cArrow = 1;
            stopFlashAll();
            coloursMenuSwitch = 4;
          }
          break;

        case 2:
          lcdWrite(0, 3, F("Player 2 Colour"), 'C');
          if(enter.pressed())
          {
            cArrow = 1;
            stopFlashAll();
            coloursMenuSwitch = 5;
          }
          break;

        case 3:
          lcdWrite(0, 3, F("Upper Matrix Colour"), 'L');
          if(enter.pressed())
          {
            cArrow = 1;
            stopFlashAll();
            coloursMenuSwitch = 6;
          }
          break;
      }
      break;

    case 4:  //Player 1:
      ledWrite("PLR. 1", 'C');
      if(back.pressed())
      {
        playerClear(p1Display);
        coloursMenuSwitch = 3;
      }
      else if(enter.pressed())
      {
        saveVal = 4;
        playerClear(p1Display);
        stopFlashAll();
        coloursMenuSwitch = 7;
      }
      else
      {
        colourArrow();
        colourChange(p1R, p1G, p1B, 1000, 1300, 1600);
        playerFill(p1Display, p1R, p1G, p1B);
        lcdWrite(17, 0, F("P1"), 'L', 3);
      }
      break;

    case 5:  //Player 2:
      ledWrite("PLR. 2", 'C');
      if(back.pressed())
      {
        playerClear(p2Display);
        coloursMenuSwitch = 3;
      }
      else if(enter.pressed())
      {
        saveVal = 5;
        playerClear(p2Display);
        stopFlashAll();
        coloursMenuSwitch = 7;
      }
      else
      {
        colourArrow();
        colourChange(p2R, p2G, p2B, 2000, 2300, 2600);
        playerFill(p2Display, p2R, p2G, p2B);
        lcdWrite(17, 0, F("P2"), 'L', 3);
      }
      break;

    case 6:  //Upper Matrix: 
      ledWrite("t0P", 'C');
      if(back.pressed())
      {
        playerClear(p1Display);
        playerClear(p2Display);
        coloursMenuSwitch = 3;
      }
      else if(enter.pressed())
      {
        saveVal = 6;
        playerClear(p1Display);
        playerClear(p2Display);
        stopFlashAll();
        coloursMenuSwitch = 7;
      }
      else
      {
        colourArrow();
        colourChange(umR, umG, umB, 3000, 3300, 3600);
        playerFill(p1Display, umR, umG, umB);
        playerFill(p2Display, umR, umG, umB);
        lcdWrite(17, 0, F("UD"), 'L', 3);
      }
      break;

    case 7:
      states = saveCase;
      break;

    default:
      coloursMenuSwitch = 0;
      break;
  }
}
//End Colours Menu




//Colour Change:
void colourChange(byte & r, byte & g, byte & b, int ri, int gi, int bi)
{
  
  lcdWrite(0, 0, F("U/D = + / - Val  "), 'C', 17);
  lcdWrite(0, 1, F("L/R = Colour Select"), 'L');
  lcdWrite(0, 3, F("  "));
  lcdWrite(2, 3, String(r), 'C', 3);
  lcdWrite(5, 3, F("   "));
  lcdWrite(8, 3, String(g), 'C', 3);
  lcdWrite(11, 3, F("   "));
  lcdWrite(14, 3, String(b), 'C', 3);
  lcdWrite(17, 3, F("   "));
  
  if(up.pressed())
  {
    switch(cArrow)
    {
      case 1:
        r ++;
        if(r >= 255)
        {
          r = 255;
        }
        serialSend(r + ri);
        break;

      case 2:
        g ++;
        if(g >= 255)
        {
          g = 255;
        }
        serialSend(g + gi);
        break;

      case 3:
        b ++;
        if(b >= 255)
        {
          b = 255;
        }
        serialSend(b + bi);
        break;
    }
  }
  else if(down.pressed())
  {
    switch(cArrow)
    {
      case 1:
        r --;
        if(r <= 0)
        {
          r = 0;
        }
        serialSend(r + ri);
        break;

      case 2:
        g --;
        if(g <= 0)
        {
          g = 0;
        }
        serialSend(g + gi);
        break;

      case 3:
        b --;
        if(b <= 0)
        {
          b = 0;
        }
        serialSend(b + bi);
        break;
    }
  }
}
//End Colour Change




//Arrow:
void colourArrow()
{
  String ss = " ";

  //Buttons LEDs Handler:
  if(cArrow != 1 && cArrow != 3)
  {
    flashButton(upLED, downLED, leftLED, rightLED, enterLED, backLED);
  }
  else if(cArrow == 1)
  {
    stopFlashSingle(leftLED);
    flashButton(upLED, downLED, rightLED, enterLED, backLED);
  }
  else if(cArrow == 3)
  {
    stopFlashSingle(rightLED);
    flashButton(upLED, downLED, leftLED, enterLED, backLED);
  }
  //End Buttons LEDs Handler
  
  lcdWrite(2, 2, F("RED"));
  lcdWrite(7, 2, F("GREEN"));
  lcdWrite(14, 2, F("BLUE"));

  if(left.pressed())
  {
    cArrow --;
    if(cArrow <= 1)
    {
      cArrow = 1;
    }
  }
  else if(right.pressed())
  {
    cArrow ++;
    if(cArrow >= 4)
    {
      cArrow = 3;
    }
  }
  
  switch(cArrow)
  {
    case 0: break;
    
    case 1:
      specChar(1, 2, 1);
      lcdWrite(6, 2, String(ss));
      lcdWrite(13, 2, String(ss));
      break;
      
    case 2:
      specChar(6, 2, 1);
      lcdWrite(1, 2, String(ss));
      lcdWrite(13, 2, String(ss));
      break;
      
    case 3:
      specChar(13, 2, 1);
      lcdWrite(1, 2, String(ss));
      lcdWrite(6, 2, String(ss));
      break;
      
    default: cArrow = 1; break;
  }
}
//End Arrow
