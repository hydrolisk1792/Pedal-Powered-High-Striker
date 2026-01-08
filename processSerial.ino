//Process the number data from Vault Input:
void processData(const long n)
{
  Serial1.println(n);
  Serial.println(n);  //Test Only

  switch(n)
  {
    case 0: /*Do Nothing Here*/ break;
    case 100 ... 190: countdown = (n - 100); break;  //Read Timer Set Data from Main:
    case 200: gameState = 0; break;  //Game Starting
    case 201: gameState = 1; break;  //Game Playing
    case 202: gameState = 2; break;  //Game Ending
    case 203: gameState = 3; break;  //Player 1 Winner
    case 204: gameState = 4; break;  //Player 2 Winner
    case 205: gameState = 5; break;  //Tie Game
    case 300 ... 555: p1Points = (n - 300); break;  //Player 1 Points
    case 600 ... 855: p2Points = (n - 600); break;  //Player 2 Points
    case 9998: states = clearAll; break;  //Is Game Idle?
    case 9999: states = gameCase; break;  //Is in Game?
  }
}
//End Process




//Process the input data from Vault
void processInput()
{
  static long receivedData = 0;
  static boolean neg = false;
  int serialData = Serial1.read();
  
  switch(serialData)
  {
    case endDelimiter:
      if(neg) {processData(- receivedData);}
      else {processData(receivedData);}
      //Fall through on purpose for new number.  No "break;" here
    case startDelimiter:
      receivedData = 0;
      neg = false;
      break;
      
    case '0' ... '9':
      receivedData *= 10;
      receivedData += serialData - '0';
      break;
      
    case '-':
      neg = true;
      break;
  }
}
//End Process
