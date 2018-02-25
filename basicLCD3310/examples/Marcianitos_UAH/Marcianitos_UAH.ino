
#define NUM_OBJECTS 3
#define NUM_MISSILS 4
#define PROPERTIES  5
#define POS_X  0
#define POS_Y 1
#define VEL_X 2
#define VEL_Y 3
#define VISIBLE 4  // Alive or not the objets

#define ALIVE 1 
#define DEAD  0

#include "Wire.h"       //Libreria I2C
#include "WiiChuck.h"   //Libreria WiiChuck
#include "basicLCD3310.h"   //Libreria WiiChuck
#include <DistanceSRF04.h>

  // General Game Func and Variables
  void init_game();
  void update_game(int recX, int recY, char shoot, char explode, int vel_ms); 
  // if explode == 1, it kills all the objects and substract 10 kills.
  
  int i,j;
  int inv = 0;
  int cont_inv = 0;
  unsigned char objects[NUM_OBJECTS][PROPERTIES];
  unsigned char missils[NUM_MISSILS][PROPERTIES];
  char killed[3];
  String str;
  int kills = 0;
  
  // CONTROLLER VARIABLES
  int nunX;
  int nunY;
  WiiChuck chuck = WiiChuck();  //Instancia de WiiChuck
  int accelX;
  DistanceSRF04 Dist;
  int distance;
  
  int potenciometer;

  int pushButton = 10;
  int buttonState;
  
void setup(void){
    Serial.begin(9600);    //Iniciamos comunicacion serie
    chuck.begin();         //Iniciamos WiiChuck
    Dist.begin(8,9);
    pinMode(pushButton, INPUT);  // BUTTON
    
    LcdInitialise();
    LcdClear();
    delay(500);
    LcdWrite(LCD_C, 0x08 );
    init_game();
}


void loop(void){
  /*
  // Controlled by nunchuck 1
  chuck.update();  
  nunY = (int)chuck.readJoyY();
  nunY = 24 + ((-nunY)*LCD_Y)/(255 + 120);
  update_game(5,nunY, (int)chuck.cPressed(),0, 100);
  
  
  */
  // Controlled by nunchuck 1
  chuck.update();  
  accelX = (int)chuck.readAccelX();
  accelX = ((accelX + 255)*LCD_Y)/(512);
  update_game(5,accelX, (int)chuck.cPressed(),(int)chuck.zPressed(), 100);
  /*
  // Controlled by SRF04
  distance = Dist.getDistanceCentimeter();
  distance = ((distance - 10)*LCD_Y)/(15);
  update_game(5,distance, 1,0, 100);
  */
  /*
   // Controlled by button and potenciometer
  potenciometer = analogRead(A0);
  potenciometer = (( potenciometer  - 20 )*LCD_Y)/(660);
  buttonState = digitalRead(pushButton);
  buttonState ^= 1;
  update_game(5,potenciometer, buttonState ,0, 100);
   */
}




// GAME FUNCTIONS
  void init_game() {
      for ( i = 0; i < NUM_OBJECTS; i++) {
        for ( j = 0; j < PROPERTIES; j++) {
           objects[i][j] = 0;
        }
      }
    for ( i = 0; i < NUM_MISSILS; i++) {
      for ( j = 0; j < PROPERTIES; j++) {
         missils[i][j] = 0;
      }
    }  
  for ( i = 0; i < NUM_OBJECTS; i++) {
         objects[i][POS_X] = LCD_X - 10;
         objects[i][POS_Y] = rand() % 5;
         objects[i][VEL_X] = 1 + rand() % 2;
         objects[i][VISIBLE] = ALIVE;
  }
}


 void update_game(int recX, int recY, char shoot,char explode, int vel_ms){
  
   if (inv == 1) {   // Creating hit effect with the screen inversion
      cont_inv++;
      if (cont_inv == 2){
        inv ^= 1;
        cont_inv = 0;
      }
   }
   LcdWrite(LCD_C, 0x0C + inv );  // Refresh screen
  gotoXY(20, 1);
  LcdString("  ");  
  gotoXY(20, 1);
  str = String(kills);
  str.toCharArray(killed,3);
  LcdString(killed);
  
 if (explode == 1) {   // IF we choose explosion
   if (kills >= 10) {
     kills -= 10;
     inv = 1;
      for ( i = 0; i < NUM_OBJECTS; i++) {
         objects[i][POS_X] = LCD_X - 10;
         objects[i][POS_Y] = rand() % 5;
         objects[i][VEL_X] = 1 + rand() % 2;
         objects[i][VISIBLE] = ALIVE;
      } 
   }
 }
 else {
     
 // CHECK FOR SHOOTING 
 if (shoot == 1) { 
   for (i = 0; i < NUM_MISSILS; i++) {
      if (missils[i][VISIBLE] == DEAD ) {
          missils[i][VISIBLE] = ALIVE;
          missils[i][POS_X] = recX + 5;
          missils[i][POS_Y] = recY/8 ;
          if (recY % 8 < 4) missils[i][POS_Y]--;
          break;
      }
   }
 }
 
  // Check objects out of bounds
  for ( i = 0; i < NUM_OBJECTS; i++) {
    if (objects[i][VISIBLE] == ALIVE ) {
    if (objects[i][POS_X] < 10 ) {  // We lost 
         inv = 1;
         kills = 0;
         objects[i][POS_X] = LCD_X - 5;
         objects[i][POS_Y] = rand() % 5;
         objects[i][VEL_X] = 1 + rand() % 2;
    }
    }
  }
  
   // Check missils out of bounds
 for ( i = 0; i < NUM_MISSILS; i++) {
    if (missils[i][VISIBLE] == ALIVE ) {
    if (missils[i][POS_X] > 80 ) {
         missils[i][VISIBLE] = DEAD;
    }
    }
  } 
  // Check collisions
   for ( i = 0; i < NUM_MISSILS; i++) {
    if (missils[i][VISIBLE] == ALIVE ) {
      for ( j = 0; j < NUM_OBJECTS; j++) {
        if (objects[j][VISIBLE] == ALIVE ) {
             if (missils[i][POS_Y] == objects[j][POS_Y]){
               if ( abs(missils[i][POS_X] - objects[j][POS_X]) < 5)  {
                     kills++;
                     missils[i][VISIBLE] = DEAD;
                     objects[j][POS_X] = LCD_X - 5;
                     objects[j][POS_Y] = rand() % 5;
                     objects[j][VEL_X] = 1 + rand() % 2;  
               }
             }
        }
        }
    }
  } 
 }
  // Draw objets
 drawRec (recX,recY);
  for ( i = 0; i < NUM_OBJECTS; i++) {
    objects[i][POS_X] -= objects[i][VEL_X];
    WrChar('$',objects[i][POS_X], objects[i][POS_Y]);
  }
   for ( i = 0; i < NUM_MISSILS; i++) {
       if (missils[i][VISIBLE] == ALIVE ) {
          missils[i][POS_X] += 5;
          WrChar('>',missils[i][POS_X], missils[i][POS_Y]);
       }
  }  

  delay(vel_ms);
  //delete objects
  eraseRec (recX,recY);
   for ( i = 0; i < NUM_OBJECTS; i++) {
    if (objects[i][VISIBLE] == ALIVE ) {
      DelChar('$',objects[i][POS_X], objects[i][POS_Y]);
    }
   }
    for ( i = 0; i < NUM_MISSILS; i++) {

    if (missils[i][VISIBLE] == ALIVE ) {
       DelChar('>',missils[i][POS_X], missils[i][POS_Y]);
    }
  } 
 }

