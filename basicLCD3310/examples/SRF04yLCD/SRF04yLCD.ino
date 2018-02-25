#include <DistanceSRF04.h>
#include "basicLCD3310.h"

DistanceSRF04 Dist;
int distance;
char dis_c[6];
String dis_s;
void setup()
{
  Serial.begin(9600);
  Dist.begin(8,9);

  LcdInitialise();
  LcdClear();
  gotoXY(15, 1);
  LcdString("DISTANCE (cm)");
  delay(500);
  LcdWrite(LCD_C, 0x08 );
}

void loop()
{
  distance = Dist.getDistanceCentimeter();
  gotoXY(35, 3);
  LcdString("     ");
  gotoXY(35, 3);
  dis_s = String(distance);
  dis_s.toCharArray(dis_c,6);
  LcdString(dis_c);
  LcdWrite(LCD_C, 0x0C );
  delay(50); //make it readable
}
