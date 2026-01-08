//Write to the Matrix
void ledWrite(const char p, byte c, byte d, String text, byte r, byte g, byte b)
{
  switch(p)
  {
    case 'L':
      p1Matrix.fillScreen(0);
      p1Matrix.setTextColor(p1Matrix.Color(r, g, b));
      p1Matrix.setCursor(c, d);
      p1Matrix.print(text);
      p1Matrix.show();
      break;

    case 'R':
      p2Matrix.fillScreen(0);
      p2Matrix.setTextColor(p1Matrix.Color(r, g, b));
      p2Matrix.setCursor(c, d);
      p2Matrix.print(text);
      p2Matrix.show();
      break;

    case 'U':
      upperMatrix.fillScreen(0);
      upperMatrix.setTextColor(p1Matrix.Color(r, g, b));
      upperMatrix.setCursor(c, d);
      upperMatrix.print(text);
      upperMatrix.show();
      break;
  }
}
//Write to the Matrix
