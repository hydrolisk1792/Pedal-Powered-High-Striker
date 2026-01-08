//Scroll Text:
void scrollText(String text, int t)
{
  static unsigned long scrollMillis = millis();
  //uint16_t red = upperMatrix.Color(255, 0, 0);
  int textLength = text.length();
  int maxDisplacement = textLength * charPixels;
  
  upperMatrix.fillScreen(0);
  upperMatrix.setTextColor(upperMatrix.Color(umR, umG, umB));
  upperMatrix.setCursor(starting, 0);
  upperMatrix.print(text);

  if(millis() - scrollMillis > t)
  {
    scrollMillis = millis();
    if(--starting < -maxDisplacement)
    {
      starting = upperMatrix.width();
    }
  }
  upperMatrix.show();
}
//End Scroll Text
