//Save:
void save()
{
  switch(saveVal)
  {
    case 0: break;
    case 1: saveHandler(1, timer); break;  //Save Timer Data
    case 2: saveHandler(2, increment); break;  //Save Increment Data
    case 3: saveHandler(3, brightness); break;  //Save Brightness Data
    case 4: ledSaveHandler(10, 11, 12, p1R, p1G, p1B); break;  //Player 1 Colour Data
    case 5: ledSaveHandler(13, 14, 15, p2R, p2G, p2B);break;  //Player 2 Colour Data
    case 6: ledSaveHandler(16, 17, 18, umR, umG, umB);break;  //Upper Matrix Colour Data
    case 7: saveHandler(4, threshold); break;  //Save Threshold Data
    case 8: saveHandler(5, BL); break;  //Save LCD Backlight Data
    case 9: saveHandler(6, pBrightness); break;  //Save Player Display Brightness Data
    default: return;
  }
}
//End Save




//LED Save Handler
void ledSaveHandler(byte cell1, byte cell2, byte cell3, byte var1, byte var2, byte var3)
{
  switch(cellSwitch)
  {
    case 0:
      ledWrite("-5AU1Ng-");
      lcdWrite(0, 0, deadspace20);
      lcdWrite(0, 1, F("SAVING TO ROM"), 'C');
      lcdWrite(0, 2, F("DO NOT UNPLUG"), 'C');
      lcdWrite(0, 3, deadspace20);
      EEPROM.update(cell1, var1);
      delay(100);
      EEPROM.update(cell2, var2);
      delay(100);
      EEPROM.update(cell3, var3);
      cellSwitch = 1;
      break;

    case 1:
      delay(1500);
      coloursMenuSwitch = 3;
      states = coloursMenuCase;
      break;
  }
}
//End LED Save Handler




//Save Handler:
void saveHandler(byte cell, byte var)
{
  switch(cellSwitch)
  {
    case 0:
      ledWrite("-5AU1Ng-");
      lcdWrite(0, 0, deadspace20);
      lcdWrite(0, 1, F("SAVING TO ROM"), 'C');
      lcdWrite(0, 2, F("DO NOT UNPLUG"), 'C');
      lcdWrite(0, 3, deadspace20);
      EEPROM.update(cell, var);
      cellSwitch = 1;
      break;

    case 1:
      delay(1500);
      serviceSwitch = 3;
      states = serviceCase;
      break;
  }
}
//End Save Handler
