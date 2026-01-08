//Bootup Sequence:
void boot()
{
  static byte syncWait = 250;
  switch(bootupSwitch)
  {
    case 0:
      ledWrite("5yNC1Ng", 'L');
      //lcdWrite(0, 0, F("***Syncing Data***"), 'C');
      lcdWrite(0, 1, deadspace20);
      lcdWrite(0, 2, F("AE&ES"), 'C');
      lcdWrite(0, 3, F("E.C.I. 2026"), 'C');
      bootupSwitch = 1;
      break;

    case 1:  //Sync:
      lcdWrite(0, 0, F("***Syncing Data***"), 'C');
      serialSend(timer + 100);
      digitalWrite(upLED, HIGH);
      delay(syncWait);
      serialSend(increment + 200);
      digitalWrite(downLED, HIGH);
      delay(syncWait);
      serialSend(brightness + 300);
      digitalWrite(leftLED, HIGH);
      playerFill(p1Display, 255, 0, 0);
      playerFill(p2Display, 255, 0, 0);
      delay(syncWait);
      serialSend(threshold + 560);
      digitalWrite(rightLED, HIGH);
      playerFill(p1Display, 0, 255, 0);
      playerFill(p2Display, 0, 255, 0);
      delay(syncWait);
      serialSend(p1R + 1000);
      digitalWrite(enterLED, HIGH);
      playerFill(p1Display, 0, 0, 255);
      playerFill(p2Display, 0, 0, 255);
      delay(syncWait);
      serialSend(p1G + 1300);
      digitalWrite(backLED, HIGH);
      playerFill(p1Display, 255, 255, 0);
      playerFill(p2Display, 255, 255, 0);
      delay(syncWait);
      serialSend(p1B + 1600);
      digitalWrite(startLED, HIGH);
      playerFill(p1Display, 255, 0, 255);
      playerFill(p2Display, 255, 0, 255);
      delay(syncWait);
      serialSend(p2R + 2000);
      digitalWrite(resetLED, HIGH);
      playerFill(p1Display, 0, 255, 255);
      playerFill(p2Display, 0, 255, 255);
      delay(syncWait);
      serialSend(p2G + 2300);
      delay(syncWait);
      serialSend(p2B + 2600);
      delay(syncWait);
      serialSend(umR + 3000);
      delay(syncWait);
      serialSend(umG + 3300);
      delay(syncWait);
      serialSend(umB + 3600);
      lcdWrite(0, 0, F("***Data Synced***"), 'C');
      ledWrite("d0NE", 'C');
      delay(3000);
      playerClear(p1Display);
      playerClear(p2Display);
      stopFlashAll();
      bootupSwitch = 2;
      break;

    case 2:
      digitalWrite(bootstrap, LOW);
      states = idle;
      break;
  }
}
//End Bootup Squence
