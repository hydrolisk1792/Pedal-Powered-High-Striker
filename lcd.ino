//Make Spaces:
String makeSpaces(byte count)
{
  String s = "";
  for(byte i = 0; i < count; i++) s += ' ';
  return s;
}
//End Make Spaces




//-----------------------------------------------------------Write to LCD:--------------------------------------------------------------
void lcdWrite(const byte col, const byte line, const String & text, char just = 'A', const byte lineWidth = 20)
{
  String padText = text;
  int spacesLeft = 0;
  int spacesRight = 0;
  int textLen = padText.length();

  if(textLen > lineWidth)
  {
    padText = padText.substring(0, lineWidth);  //Trim if too long
    textLen = lineWidth; //Update Length for Padding Calculations
  }

  switch(just)
  {
    case 'C': //Centre
      spacesLeft = (lineWidth - textLen) / 2;
      spacesRight = lineWidth - textLen - spacesLeft;
      padText = makeSpaces(spacesLeft) + padText + makeSpaces(spacesRight);
      break;

    case 'R': //Right
      spacesLeft = lineWidth - textLen;
      padText = makeSpaces(spacesLeft) + padText;
      break;

    case 'L': //Left
      spacesRight = lineWidth - textLen;
      padText = padText + makeSpaces(spacesRight);
      break;

    default: //'A' or invalid
      break;
  }
  lcd.setCursor(col, line);
  lcd.print(padText);
}

//Overload for Flash strings (F())
void lcdWrite(const byte col, const byte line, const __FlashStringHelper * textF, char just = 'A', const byte lineWidth = 20)
{
  lcdWrite(col, line, String(textF), just, lineWidth); // Convert Flash to String and reuse main function
}

//Overload for SRAM literals
void lcdWrite(const byte col, const byte line, const char * text, char just = 'A', const byte lineWidth = 20)
{
  lcdWrite(col, line, String(text), just, lineWidth); // Convert to String
}
//------------------------------------------------------------End Write to LCD----------------------------------------------------------------------




//Special Characters Handler:
void specCharHandler(byte col, byte row, long a, long b, long c, long d, long e, long f, long g, long h)
{
  byte image1[8] = {a, b, c, d, e, f, g, h};
  lcd.createChar(2, image1);
  lcd.setCursor(col, row);
  lcd.write(2);
}
//End Special Characters Handler




//Special Characters:
void specChar(byte col, byte row, byte select)
{
  switch(select)
  {
    case 0:
      //Do Nothing Here;
      break;
    case 1:  //Right Arrow
      specCharHandler(col, row, B00000, B00100, B00010, B11111, B00010, B00100, B00000, B00000);
      break;
    case 2:  //Block
      specCharHandler(col, row, B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111);
      break;
    case 3:  //Button Up
      specCharHandler(col, row, B00000, B00000, B01110, B01110, B01110, B11111, B11111, B00000);
      break;
    case 4:  //Button Down
      specCharHandler(col, row, B00000, B00000, B00000, B00000, B01110, B11111, B11111, B00000);
      break;
    case 7:  //Down Arrrow
      specCharHandler(col, row, B00100, B00100, B00100, B00100, B10101, B01110, B00100, B00000);
      break;
    default:
      select = 0;
      return;
  }
}
//End Special Characters




//Arrow Helper
void arrow(byte x)
{
  const String singlespace = " ";
  
  switch(x)
  {
    case 0:
      specChar(0, 0, 1);
      lcdWrite(0, 1, singlespace);
      lcdWrite(0, 2, singlespace);
      lcdWrite(0, 3, singlespace);
      break;

    case 1:
      lcdWrite(0, 0, singlespace);
      specChar(0, 1, 1);
      lcdWrite(0, 2, singlespace);
      lcdWrite(0, 3, singlespace);
      break;

    case 2:
      lcdWrite(0, 0, singlespace);
      lcdWrite(0, 1, singlespace);
      specChar(0, 2, 1);
      lcdWrite(0, 3, singlespace);
      break;

    case 3:
      lcdWrite(0, 0, singlespace);
      lcdWrite(0, 1, singlespace);
      lcdWrite(0, 2, singlespace);
      specChar(0, 3, 1);
      break;
  }
}
//End Arrow Helper
