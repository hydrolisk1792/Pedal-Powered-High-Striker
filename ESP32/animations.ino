//Idle Animations:
void idleAni()
{
  static unsigned long idleAniMillis = millis();
  
  if(millis() - idleAniMillis > 60000)
  {
    idleAniMillis = millis();
    idleAniSwitch ++;
    if(idleAniSwitch >= 3)
    {
      idleAniSwitch = 0;
    }
  }
        
  switch(idleAniSwitch)
  {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;

    default:
      idleAniSwitch = 0;
      return;
  }
  /*p1Matrix.fillScreen(0);
  p1Matrix.setTextColor(p1Matrix.Color(255, 0, 0));
  p1Matrix.clear();
  p1Matrix.setCursor(0, 0);
  p1Matrix.print("You're the Looser");
  p1Matrix.show();

  p2Matrix.fillScreen(0);
  p2Matrix.setTextColor(p1Matrix.Color(0, 255, 0));
  p2Matrix.clear();
  p2Matrix.setCursor(0, 0);
  p2Matrix.print("You're the Winner");
  p2Matrix.show();*/
  
  snowSparkle();
}
//End Idle Animations




//Snow Sparkle
void snowSparkle()
{
  static unsigned long snowMillis = millis();
  int index1 = random(matrixWidth * matrixHeight);
  int index2 = random(matrixWidth * matrixHeight);
  
  p1Matrix.setPixelColor(index1, p1Matrix.Color(255, 255, 255));
  p1Matrix.show();
  p2Matrix.setPixelColor(index2, p2Matrix.Color(255, 255, 255));
  p2Matrix.show();
    
  if(millis() - snowMillis > 30000)
  {
    p1Matrix.fillScreen(0);
    p2Matrix.fillScreen(0);
    p1Matrix.show();
    p2Matrix.show();
    snowMillis = millis();
  }
}
//End Snow Sparkle
