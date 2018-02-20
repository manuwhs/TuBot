#include <Arduino.h>
#include <Servo.h> 
#include <tubot_motor.h>


void MotorTubot::begin(int pin){
   minPWM = MIN_PWM;
   maxPWM = MAX_PWM;
   valorCero = (minPWM + maxPWM)/2;

  myservo.attach(pin);  
  myservo.writeMicroseconds(valorCero);  
  setSpeed(0);
}

void MotorTubot::begin(int pin, int zeroValue){
   minPWM = MIN_PWM;
   maxPWM = MAX_PWM;
  if ((zeroValue > minPWM) && (zeroValue < maxPWM)) {
    valorCero = zeroValue;
  }
  else{
    valorCero = (minPWM + maxPWM)/2;
  }  

  myservo.attach(pin);  
  myservo.writeMicroseconds(valorCero);  
  
  setSpeed(0);
}

void MotorTubot::setSpeed(int speedo){
  int speedValue;
  velocidad = speedo;
  if (speedo >= 100) speedo = 100;
  if (speedo <= -100) speedo = -100;
  
  if (speedo >= 0){
    speedValue = valorCero + ((maxPWM - valorCero)/100) * speedo; 
  } 
  else{
    speedValue = valorCero - ((minPWM - valorCero)/100) * speedo; 
  } 
  myservo.writeMicroseconds(speedValue);  
}
void MotorTubot::set_micros(int micross){
    myservo.writeMicroseconds(micross); 
  }

void MotorTubot::setZero(int zeroValue){
  if ((zeroValue > minPWM) && (zeroValue < maxPWM)) {
    valorCero = zeroValue;
  }
}

int MotorTubot::getZero(void) {
  return valorCero;
}

int MotorTubot::getSpeed(void) {
  return velocidad;

}


//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************


void MoverRobot::begin(int pin1, int pin2){

    motorIzda.begin(pin1);  
    motorDcha.begin(pin2);  
}

void MoverRobot::begin(int pin1, int pin2,int zeroValue1 ,int zeroValue2 ){
    motorIzda.begin(pin1, zeroValue1);  
    motorDcha.begin(pin2, zeroValue2); 
    
}

void MoverRobot::recto(int speedo){

    motorIzda.setSpeed(speedo);
    motorDcha.setSpeed(-speedo);
}
void MoverRobot::para(void){
  motorIzda.setSpeed(0);
  motorDcha.setSpeed(0);
}

void MoverRobot::dcha(int giro, int speedo){
  if (giro < 0) giro = -giro;
  motorIzda.setSpeed(giro + speedo);
  motorDcha.setSpeed(giro - speedo);
}

void MoverRobot::izda(int giro, int speedo){
  if (giro < 0) giro = -giro;
  motorIzda.setSpeed((-giro) + speedo);
  motorDcha.setSpeed((-giro) - speedo);
}

//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************


