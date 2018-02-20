#include <Servo.h>
#include <tubot_motor.h>

int pinmotorIzda =     9;
int pinmotorDcha =    10;
MoverRobot tubot;

void setup(){
  tubot.begin(pinmotorIzda , pinmotorDcha,1238 ,1250 );
}

void loop(){

  tubot.para();  // Parar robot
  delay(1000);   // El robot estara parado 1s
  
  tubot.recto(50); // Mover robot hacia delante
  delay(1000);     // Durante 1s
  
  tubot.dcha(20);  // Girar el robot hacia la dcha
  delay(700);      // Durante 0.7s
  
  tubot.recto(-20); // Mover robot hacia atras
  delay(1500);      // Durante 1.5s
  
  tubot.izda(40);  // Girar el robot hacia la izda
  delay(500);      // Durante 0.5s
  
}


