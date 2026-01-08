//Fill Matrix Both Players
void fillBoth(byte r, byte g, byte b)
{
  p1Matrix.fillScreen(p1Matrix.Color(r, g, b));
  p1Matrix.show();
  p2Matrix.fillScreen(p2Matrix.Color(r, g, b));
  p2Matrix.show();
}
//End Fill Matrix Both Players




//Fill Bar
void fillBar()
{
  switch(increment)
  {
    case 0:
      //Do Nothing Here
      break;

    case 1:
      p1Matrix.drawLine(1 + p1Points, 1, 1 + p1Points, 6, p1Matrix.Color(p1R, p1G, p1B));  //p1Matrix.drawLine(posX, posY, fromX, toY, Colour)
      p1Matrix.show();
      p2Matrix.drawLine(1 + p2Points, 1, 1 + p2Points, 6, p2Matrix.Color(p2R, p2G, p2B));  //p1Matrix.drawLine(posX, posY, fromX, toY, Colour)
      p2Matrix.show();
      break;

    case 2:
      p1Matrix.drawRect(1 + p1Points, 1, 2, 6, p1Matrix.Color(p1R, p1G, p1B));
      p1Matrix.show();
      p2Matrix.drawRect(1 + p2Points, 1, 2, 6, p2Matrix.Color(p2R, p2G, p2B));
      p2Matrix.show();
      break;

    case 3:
      p1Matrix.fillRect(1 + p1Points, 1, 3, 6, p1Matrix.Color(p1R, p1G, p1B));
      p1Matrix.show();
      p2Matrix.fillRect(1 + p2Points, 1, 3, 6, p2Matrix.Color(p2R, p2G, p2B));
      p2Matrix.show();
      break;

    case 4:
      p1Matrix.fillRect(1 + p1Points, 1, 4, 6, p1Matrix.Color(p1R, p1G, p1B));
      p1Matrix.show();
      p2Matrix.fillRect(1 + p2Points, 1, 4, 6, p2Matrix.Color(p2R, p2G, p2B));
      p2Matrix.show();
      break;

    case 5:
      p1Matrix.fillRect(1 + p1Points, 1, 5, 6, p1Matrix.Color(p1R, p1G, p1B));
      p1Matrix.show();
      p2Matrix.fillRect(1 + p2Points, 1, 5, 6, p2Matrix.Color(p2R, p2G, p2B));
      p2Matrix.show();
      break;

    default:
      increment = 1;
      return;
  }
}
//End Fill Bar




//Boarder
void boarder()
{
  p1Matrix.drawRect(0, 0, matrixWidth, matrixHeight, p1Matrix.Color(p1R, p1G, p1B));  //p1Matrix.drawLine(posX, posY, fromX, toY, Colour)
  p1Matrix.show();
  p2Matrix.drawRect(0, 0, matrixWidth, matrixHeight, p2Matrix.Color(p2R, p2G, p2B));  //p1Matrix.drawLine(posX, posY, fromX, toY, Colour)
  p2Matrix.show();
}
//End Boarder
