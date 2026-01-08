//Fill Whole Strip:
void playerFill(Adafruit_NeoPixel & p, byte r, byte g, byte b)
{
  p.setBrightness(pBrightnessMap);
  for(int i = 0; i < pixels; i ++)
  {
    p.setPixelColor(i, p.Color(r, g, b));
    p.show();
  }
}
//End Player Fill




//Clear Whole Strip
void playerClear(Adafruit_NeoPixel & p)
{
  for(int i = 0; i < pixels; i ++)
  {
    p.setPixelColor(i, p.Color(0, 0, 0));
    p.show();
  }
}
//End Clear Whole Strip
