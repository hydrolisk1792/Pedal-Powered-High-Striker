//Send Data:
void serialSend(const int x)
{
  String sending = startDelimiter + String(x) + endDelimiter;
  Serial2.print(String(sending));
  Serial2.println();
  Serial.println(x);
}
//End Send Data
