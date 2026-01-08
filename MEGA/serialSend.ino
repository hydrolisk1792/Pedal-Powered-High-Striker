//Send Data:
void serialSend(const int x)
{
  String sending = startDelimiter + String(x) + endDelimiter;
  Serial1.print(String(sending));
  Serial1.println();
}
//End Send Data
