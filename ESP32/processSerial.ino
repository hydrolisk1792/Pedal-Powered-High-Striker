//Process the number data from Control System Input:
void processData(const long n)
{
  Serial2.println(n);
  Serial.println(n);  //Test Only

  switch(n)
  {
    case 0: /*Do Nothing Here*/ break;
    case 100 ... 190: timer = (n - 100); break;  //Set Game Timer Value
    case 200 ... 205: increment = (n - 200); break;  //Set Increment Value
    case 300 ... 555: brightness = (n - 300); break;  //Matrix Brightness Setting
    case 560 ... 565: threshold = (n - 560); break;  //Threshold Setting
    case 1000 ... 1255: p1R = (n - 1000); break;  //Player 1 Red Value
    case 1300 ... 1555: p1G = (n - 1300); break;  //Player 1 Green Value
    case 1600 ... 1855: p1B = (n - 1600); break;  //Player 1 Blue Value
    case 2000 ... 2255: p2R = (n - 2000); break;  //Player 2 Red Value
    case 2300 ... 2555: p2G = (n - 2300); break;  //Player 2 Green Value
    case 2600 ... 2855: p2B = (n - 2600); break;  //Player 2 Blue Value
    case 3000 ... 3255: umR = (n - 3000); break;  //Upper Matrix Red Value
    case 3300 ... 3555: umG = (n - 3300); break;  //Upper Matrix Green Value
    case 3600 ... 3855: umB = (n - 3600); break;  //Upper Matrix Blue Value
    case 9876: states = serviceCase; break;  //In Service Mode
    case 9877: states = exitAny; break;  //Exit Service Mode
  }
}
//End Process




//Process the input data from Control System:
void processInput()
{
  static long receivedData = 0;
  static boolean neg = false;
  int serialData = Serial2.read();
  
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
