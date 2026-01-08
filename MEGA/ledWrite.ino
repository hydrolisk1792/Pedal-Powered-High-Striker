//LED Write:
void ledWrite(byte start, const String & text, char just, byte fieldWidth)
{
  char chars[8];
  bool dp[8];

  // Clear buffers
  for (byte i = 0; i < 8; i++)
  {
    chars[i] = ' ';
    dp[i] = false;
  }

  // ---------- Parse text ----------
  byte textLen = 0;
  for (byte i = 0; i < text.length() && textLen < fieldWidth; i++)
  {
    char c = text.charAt(i);

    if(c == '.')
    {
      if(textLen > 0) dp[textLen - 1] = true;
    }
    else
    {
      chars[textLen] = c;
      dp[textLen] = false;
      textLen++;
    }
  }

  // Clamp field to display
  if(start >= 8) {return;}
  if(start + fieldWidth > 8) {fieldWidth = 8 - start;}

  // ---------- Justification ----------
  byte spacesLeft = 0;

  switch(just)
  {
    case 'C':  spacesLeft = (fieldWidth - textLen) / 2; break;
    case 'R': spacesLeft = fieldWidth - textLen; break;
    case 'L':
    default:
      spacesLeft = 0;
      break;
  }

  // ---------- Output ----------
  for(byte i = 0; i < fieldWidth; i++)
  {
    int src = i - spacesLeft;

    char c = ' ';
    bool d = false;

    if(src >= 0 && src < textLen)
    {
      c = chars[src];
      d = dp[src];
    }

    byte digit = 7 - (start + i);
    led7segWrite(digit, c, d);
  }
}

void ledWrite(const String & text, char just = 'A')
{
  ledWrite(0, text, just, 8);
}

void ledWrite(byte start, const String & text, char just = 'A')
{
  ledWrite(start, text, just, 8 - start);
}

//End LED Write




//LED Character Selector:
void led7segWrite(byte digit, int character, boolean dp)
{
  switch(character)
  {
    case 'n': led7seg.setRow(0, digit, dp ? B10010101 : B00010101); break;  //'n'
    case 'N':  led7seg.setRow(0, digit, dp ? B11110110 : B01110110); break;  //'N'
    case 'C':  led7seg.setRow(0, digit, dp ? B11001110 : B01001110); break;  //'C'
    case 'o':  led7seg.setRow(0, digit, dp ? B10011101 : B00011101); break;  //'o'
    case 'r':  led7seg.setRow(0, digit, dp ? B10000101 : B00000101); break;  //'r'
    case 'R':  led7seg.setRow(0, digit, dp ? B11100110 : B01100110); break;  //'R'
    case 't': led7seg.setRow(0, digit, dp ? B10001111 : B00001111); break;  //'t'
    case 'u': led7seg.setRow(0, digit, dp ? B10011100 : B00011100); break; //'u'
    case 'U': led7seg.setRow(0, digit, dp ? B10111110 : B00111110); break;  //'U'
    case 'y':  led7seg.setRow(0, digit, dp ? B10111011 : B00111011); break;  //'y'
    case 'g': led7seg.setRow(0, digit, dp ? B11111011 : B01111011);break;  //'g'
    case ' ': led7seg.setRow(0, digit, dp ? B10000000 : B00000000); break;  //' '  "Space"
    default: led7seg.setChar(0, digit, character, dp); break;  //Default cCase for Other Characters
  }
}
//End LED Character Selector:
