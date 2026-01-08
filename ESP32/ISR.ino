//ISR 1:
void IRAM_ATTR isr1()
{
  opto1.numBroken1 ++;
  opto1.broken1 = true;
}
//End ISR 1




//ISR2
void IRAM_ATTR isr2()
{
  opto2.numBroken2 ++;
  opto2.broken2 = true;
}
//End ISR2
