#include <Arduino.h> 
#include "basicLCD3310.h"

void LcdCharacter(char character)
{
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
}

void WrChar(char character, int x, int y)
{
  gotoXY(x,y+1);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
}

void DelChar(char character, int x, int y)
{
  gotoXY(x,y+1);
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, 0x0);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdClear(void){
  int i, j;
  for (i = 0; i <  LCD_Y/ 8 + 1; i++){
     gotoXY(0,i);
      for (j = 0; j <  LCD_X; j++){
        LcdWrite(LCD_D, 0x00);
      }
  }
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  
  LcdWrite(LCD_C, LCDEXTENDED );  // LCD Extended Commands.
  LcdWrite(LCD_C, LCDCONTRAST);  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, LCDTEMPC  );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, LCDMODE );  // LCD bias mode 1:48. //0x13
  
  LcdWrite(LCD_C,LCDBCMODE );  // LCD Basic commands
  LcdWrite(LCD_C, LCDCONTROL );// LCD in normal mode. (not inverted or black)
}
// Origen Up left

void LcdString(char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

// gotoXY routine to position cursor 
// x - range: 0 to 84
// y - range: 0 to 5

void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column. // 0-83
  LcdWrite( 0, 0x40 | y);  // Row.  // 0 - 5

}

void drawRec(int x, int y){
  unsigned char  i,j;  
  unsigned char h1 = 0, h2 = 0;
  for(i= y%8 ; i < 8 ; i++){
     h1 |= 1 <<  i;
  }
   for(i= 0 ; i < y%8; i++){
     h2 |= 1 <<  i;
  }
   gotoXY (x,y/8);
   for(i= 0 ; i < 8; i++){ // top
          LcdWrite(LCD_D, h1);
    }
     gotoXY (x,y/8 + 1);
    for(i= 0 ; i < 8; i++){ // top
          LcdWrite(LCD_D, h2);
    }
 } 
 	
 void eraseRec(int x, int y){
  unsigned char  i,j;  
  unsigned char h1 = 0, h2 = 0;

   gotoXY (x,y/8);
   for(i= 0 ; i < 8; i++){ // top
          LcdWrite(LCD_D, 0);
    }
     gotoXY (x,y/8 + 1);
    for(i= 0 ; i < 8; i++){ // top
          LcdWrite(LCD_D, 0);
    }
 }    

void setpix(int x, int y){
    char bit_y = y % 8;
    gotoXY (x,y/8);
    LcdWrite(LCD_D, 1 << bit_y);
}






