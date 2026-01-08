//Game Start:
void gameStartHandler()
{
  if(reset.pressed()) {states = exitAny;}
  
  switch(gameStartSwitch)
  {
    case 0:
      serialSend(9999);
      delay(100);
      serialSend(200);
      delay(1000);
      gameStartSwitch = 1;
      break;

    case 1:  //Ready
      ledWrite('U', 1, 0, "READY", 255, 0, 0);
      fillBoth(255, 0, 0);
      delay(1500);
      gameStartSwitch = 2;
      break;

    case 2:  //Set
      ledWrite('U', 7, 0, "SET", 255, 255, 0);
      fillBoth(255, 255, 0);
      delay(1500);
      gameStartSwitch = 3;
      break;

    case 3:  //Go
      ledWrite('U', 10, 0, "GO", 0, 255, 0);
      fillBoth(0, 255, 0);
      delay(1500);
      ledWrite('L', 120, 0, "GO", 0, 255, 0);
      ledWrite('R', 120, 0, "GO", 0, 255, 0);
      delay(500);
      fillBoth(0, 0, 0);
      states = gamePlayCase;
      break;

    default:
      gameStartSwitch = 0;
      return;
  }
}
//End Game Start




//Game Play:
void gamePlayHandler()
{
  unsigned long currentTimer = millis();  //Current Timer Time

  if(reset.pressed()) {states = exitAny;}

  switch(gamePlaySwitch)
  {
    case 0:  //Soft Enter:
      serialSend(201);
      delay(100);
      setTimer = (timer * 1000) + 1000;
      boarder();
      threshTemp = 0;
      gamePlaySwitch = 1;
      break;

    case 1:  //Game Play & Scoring
      fillBar();

      if(opto1.broken1)
      {
        threshTemp ++;
        if(threshTemp == threshold)
        {
          p1Points += increment;
          threshTemp = 0;
        }
        opto1.broken1 = false;
      }
      if(opto2.broken2)
      {
        threshTemp ++;
        if(threshTemp == threshold)
        {
          p2Points += increment;
          threshTemp = 0;
        }
        opto2.broken2 = false;
      }
      //Matrix Code Here as well.
      
      if(currentTimer - prevTimer >= intervalTimer)
      {
        prevTimer = currentTimer;

        setTimer -= 1000;
        ledWrite('U', 0, 0, "T-" + String(setTimer / 1000), 255, 0, 0);
        serialSend((setTimer / 1000) + 100);

        if(setTimer <= 0 || p1Points >= 222 || p2Points >= 222) {gamePlaySwitch = 2;}  //End Game
      }
      break;

    case 2:
      states = endGameCase;
      break;

    default:
      gamePlaySwitch = 0;
      return;
  }
}
//End Game Play




//Game Over:
void gameOverHandler()
{
  static unsigned long flashWinner = millis();
  
  switch(gameOverSwitch)
  {
    case 0:
      serialSend(202);
      delay(100);
      fillBoth(0, 0, 0);
      flashWinner = millis();
      if(flashTimes > 0) {flashTimes = 0;}
      gameOverSwitch = 1;
      break;

    case 1:  //Flow Control:
      serialSend(p1Points + 300);
      delay(10);
      serialSend(p2Points + 600);
      delay(10);
      if(p1Points > p2Points)
      {
        serialSend(203);
        gameOverSwitch = 2;
      }
      else if(p1Points < p2Points)
      {
        serialSend(204);
        gameOverSwitch = 3;
      }
      else if(p2Points == p1Points)
      {
        serialSend(205);
        gameOverSwitch = 4;
      }
      break;

    case 2:  //Player 1 Wins:
      if(millis() - flashWinner > 500)
      {
        flashWinner = millis();
        flashTimes ++;
        if(flashTimes >= 9) {gameOverSwitch = 10;}
        flashWinnerFlag = !flashWinnerFlag;
      }
      if(flashWinnerFlag)
      {
        ledWrite('U', 1, 0, "Plr 1", p1R, p1G, p1B);
        p1Matrix.fillScreen(p1Matrix.Color(p1R, p1G, p1B));
        p1Matrix.show();
      }
      else
      {        
        upperMatrix.clear();
        upperMatrix.show();
        p1Matrix.fillScreen(0);
        p1Matrix.show();
      }
      break;

    case 3:  //Player 2 Wins:
      if(millis() - flashWinner > 500)
      {
        flashWinner = millis();
        flashTimes ++;
        if(flashTimes >= 9) {gameOverSwitch = 10;}
        flashWinnerFlag = !flashWinnerFlag;
      }
      if(flashWinnerFlag)
      {
        ledWrite('U', 1, 0, "Plr 2", p2R, p2G, p2B);
        p2Matrix.fillScreen(p1Matrix.Color(p2R, p2G, p2B));
        p2Matrix.show();
      }
      else
      {
        upperMatrix.clear();
        upperMatrix.show();
        p2Matrix.fillScreen(0);
        p2Matrix.show();
      }
      break;

    case 4:  //Players Tie:
      if(millis() - flashWinner > 500)
      {
        flashWinner = millis();
        flashTimes ++;
        if(flashTimes >= 9) {gameOverSwitch = 10;}
        flashWinnerFlag = !flashWinnerFlag;
      }
      if(flashWinnerFlag)
      {
        ledWrite('U', 7, 0, "TIE", p1R + p2R, p1G + p2G, p1B + p2B);
        fillBoth(p1R + p2R, p1G + p2G, p1B + p2B);
      }
      else
      {
        upperMatrix.clear();
        upperMatrix.show();
        fillBoth(0, 0, 0);
      }
      break;

    case 10:
      states = exitAny;
      break;

    default:
      gameOverSwitch = 0;
      return;
  }
}
//End Game Over
