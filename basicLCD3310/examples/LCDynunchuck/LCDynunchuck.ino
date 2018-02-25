

#include "Wire.h"       //Libreria I2C
#include "WiiChuck.h"   //Libreria WiiChuck
#include "basicLCD3310.h"   //Libreria WiiChuck
WiiChuck chuck = WiiChuck();  //Instancia de WiiChuck
 

void setup(void)
{
  Serial.begin(9600);    //Iniciamos comunicacion serie
  chuck.begin();         //Iniciamos WiiChuck
  LcdInitialise();
  LcdClear();
  gotoXY(20, 1);
  delay(500);
  LcdWrite(LCD_C, 0x08 );
}
  int nunX;
  int nunY;
  unsigned char recX;
  unsigned char recY;
  int inv = 0;
void loop(void)
{
  chuck.update();  
  if ((int)chuck.cPressed() == 1) { inv ^= 1;}
  nunX = (int)chuck.readJoyX();
  nunY = (int)chuck.readJoyY();
  recX = 42 -8 + ((nunX )*84)/(255 + 120);
  recY = 24 + ((-nunY)*48)/(255 + 120);
  
  LcdWrite(LCD_C, 0x0C + inv );

 
  drawRec (recX,recY);
  delay(50);
eraseRec (recX,recY);
  
}