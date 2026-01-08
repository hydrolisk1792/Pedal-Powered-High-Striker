//Game State:
void gameStatus()
{
  if(gameState == 1)
  {
    stopFlashSingle(upLED, downLED, leftLED, rightLED, enterLED, backLED, startLED);
    flashButton(resetLED);
  }
  else {stopFlashAll();}
  
  lcdWrite(0, 0, "Time Left: " + String(countdown) + " secs", 'L');
  lcdWrite(0, 1, "Status: ", 'C', 8);
  lcdWrite(0, 2, "Player 1 Points: " + String(p1Points), 'L');
  lcdWrite(0, 3, "Player 2 Points: " + String(p2Points), 'L');
  
  switch(gameState)
  {
    case 0: lcdWrite(8, 1, F("Starting"), 'L', 12); ledWrite("5tARt1Ng");break;
    case 1: lcdWrite(8, 1, F("Playing"), 'L', 12); ledWrite(0, "PLAy1Ng", 'L', 7); segment(0); break;
    case 2: lcdWrite(8, 1, F("Ending"), 'L', 12); ledWrite("ENd1Ng", 'L'); break;
    case 3: lcdWrite(8, 1, F("P1 Win"), 'L', 12); ledWrite(0, "P1. ", 'L', 3); ledWrite(4, String(p1Points), 'L', 7); break;
    case 4: lcdWrite(8, 1, F("P2 Win"), 'L', 12); ledWrite(0, "P2. ", 'L', 3); ledWrite(4, String(p2Points), 'L', 7);break;
    case 5: lcdWrite(8, 1, F("Tie"), 'L', 12); ledWrite("t1E. gANE"); break;
  }
}
//End Game State
