#ifndef Tubot_motor_h
#define Tubot_motor_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include <Servo.h> 
#define MIN_PWM 560
#define MAX_PWM 2150

class MotorTubot{
  private:
    int minPWM;
    int maxPWM;
    int valorCero;
    int velocidad;
    Servo myservo; 
	
  public:
    void begin (int pin);
    void begin (int pin, int zeroValue);
    void setSpeed(int speed);
    int getSpeed(); 
    void setZero(int zeroValue); 
    int getZero(void);      
	void set_micros(int micross);  
};  


class MoverRobot {

  public:
  
   MotorTubot motorDcha;  
   MotorTubot motorIzda;
   
    void begin(int pin1, int pin2);
    void begin(int pin, int pin2,int zeroValue1 ,int zeroValue2 );
    void recto(int speedo);
    void para(void);
    void dcha(int giro, int speed = 0);
    void izda(int giro, int speed = 0);
	
	
};

#endif