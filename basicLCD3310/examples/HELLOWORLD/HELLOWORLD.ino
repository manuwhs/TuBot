

#include "Wire.h"       //Libreria I2C
#include "basicLCD3310.h"   //Libreria WiiChuck

void setup(void){
  Serial.begin(9600);    //Iniciamos comunicacion serie
  LcdInitialise();
  LcdClear();
  gotoXY(15, 1);
  LcdString("HELLO WORLD");
  delay(500);
  LcdWrite(LCD_C, 0x08 );
}

char killed[3];
String str;
void loop(void)
{
  LcdWrite(LCD_C, 0x0C );
  delay(50);
}

