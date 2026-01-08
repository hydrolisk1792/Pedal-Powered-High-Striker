//Flash Button LED:
void flashButton(int a, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0, int h = 0)
{
  static unsigned long flashMillis = millis();
  static int flashInterval = 250;
  static boolean flashFlag;

  if(millis() - flashMillis >= flashInterval)
  {
    flashMillis = millis();
    flashFlag = !flashFlag;
  }
  if(flashFlag)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(h, HIGH);
  }
  else
  {
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    digitalWrite(h, LOW);
  }
}
//End Flash Button LED




//Stop Flash
void stopFlashAll(void)
{
  digitalWrite(upLED, LOW);
  digitalWrite(downLED, LOW);
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);
  digitalWrite(backLED, LOW);
  digitalWrite(enterLED, LOW);
  digitalWrite(startLED, LOW);
  digitalWrite(resetLED, LOW);
  return;
}
//End Stop Flash




//Stop Single
void stopFlashSingle(int a, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int g = 0, int h = 0)
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(h, LOW);
}
//End Stop Single
