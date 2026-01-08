//Returning
void returning()
{
  if(gameStartSwitch > 0) {gameStartSwitch = 0;}
  if(gamePlaySwitch > 0) {gamePlaySwitch = 0;}
  if(gameOverSwitch > 0) {gameOverSwitch = 0;}
  fillBoth(0, 0, 0);
  if(p1Points > 0) {p1Points = 0;}
  if(p2Points > 0) {p2Points = 0;}
  if(setTimer == 0) {setTimer = timer * 1000;}
  states = clearAll;
}
//End Returning
