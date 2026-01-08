//Segment:
void segment(byte digit)
{
  static unsigned long aniMillis = millis();
  const byte aniInterval = 100;
  
  if(millis() - aniMillis > aniInterval)
  {
    if(ani == 7)
    {
      ani = 1;
    }
    ani++;
    aniMillis = millis();
  }
  
  switch(ani)
  {
    case 0: break;
    case 1: led7seg.setRow(0, digit, B01000000); break;
    case 2: led7seg.setRow(0, digit, B00100000); break;
    case 3: led7seg.setRow(0, digit, B00010000); break;
    case 4: led7seg.setRow(0, digit, B00001000); break;
    case 5: led7seg.setRow(0, digit, B00000100); break;
    case 6: led7seg.setRow(0, digit, B00000010); break;
    default: ani = 1; return;
  }
}
//End Segment
