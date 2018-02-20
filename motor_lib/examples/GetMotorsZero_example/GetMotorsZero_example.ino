
#include <Servo.h>  // Incluímos librería de los servos
#include <tubot_motor.h> // Incluímos librería de los motores
// Pines que controlan los motores.
int pinmotorIzda =      9;
int pinmotorDcha =    10;
// Variables para los motores
MotorTubot motorIzda;
MotorTubot motorDcha;

int incomingByte = 0;

void setup(){
  Serial.begin(19200);
  motorIzda.begin(pinmotorIzda, 1238);  
  motorDcha.begin(pinmotorDcha, 1250);
}

void loop(){
  delay(200);
  Serial.println("ZeroMotorIzd      ZeroMotorDer  ");
  Serial.print(motorIzda.getZero());  
  Serial.print("       |        ");
  Serial.print(motorDcha.getZero());  
  Serial.println(" ");
  
if (Serial.available() > 0) {
     incomingByte = Serial.read();
     switch (incomingByte){
       
       //------------> Right motor <-------
       case 'l':
         motorDcha.setZero( motorDcha.getZero() + 2);
         motorDcha.setSpeed(0);
         break;
         
       case 'j':
         motorDcha.setZero( motorDcha.getZero() - 2);
         motorDcha.setSpeed(0);
         break;
 
         //------------> Left motor <-------
       case 'd':
         motorIzda.setZero( motorIzda.getZero() + 2);
         motorIzda.setSpeed(0);
         break;
         
       case 'a':
         motorIzda.setZero( motorIzda.getZero() - 2);
         motorIzda.setSpeed(0);
       break;         
     }
  }
}
