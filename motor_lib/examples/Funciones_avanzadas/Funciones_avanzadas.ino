#include <DistanceSRF04.h>
#include <Servo.h> 
#include <tubot_motor.h>
#define NEGRO_INFRARED 110
#define BLANCO_INFRARED  930

#define LUZ_LDR          100
#define AMBIENTE_LDR     800

void check_function();  // Funcion para monitorizar por teclado los sensores y actuadores
void detect_mov();      // El robot ira recto hasta toparse con un obstaculo, entonces va hacia atras
                        // y gira aleatoriamente
void sigue_luz();      // Sigue una luz
void strike();         // El robot se mueve aleatoriamente hasta encontrar un objeto y lo embiste.
void stay_in_tatami();  // Funcion que comprueba que estemos dentro del cuadrilatero, de ser asi, hace strike()
                        // De no ser asi, vuelve hacia atras y gira.
 void sigueLinea();    // El robot sigue una linea oscura en el suelo.
 
int pinLed  =          13;
int pinEco  =           2;
int pinTrigger =        3;
int pinButton =         4;
int pinmotorIzda =      9;
int pinmotorDcha =    10;
int pinPotenciometer = A0;
int pinInfraredRight = A1;
int pinInfraredLeft =  A2;
int pinLDRRight =      A3;
int pinLDRLeft =       A4;


MoverRobot tubot;
DistanceSRF04 Dist;
int distance;

int incomingByte = 0;
int button;
int potenciometer;

int infraredRight;      // Blanco -> 930   Negro -> 110
int infraredLeft;       
int LDRRight;          // 200 -> Muy iluminado    750 -> luz ambiente
int LDRLeft;

//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************

void setup(){
  Serial.begin(19200);
  Dist.begin(pinEco,pinTrigger);
  pinMode(pinLed, OUTPUT);     
  pinMode(pinButton, INPUT);  
  tubot.begin(pinmotorIzda , pinmotorDcha,1238 ,1250 );
}

void loop(){

  
  // check_function();
   detect_mov();
  // strike();
  // stay_in_tatami();
  // sigue_luz();
  // sigueLinea();
}

//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************

bool detecta_limite (int infraredValue){
  if (infraredValue < (NEGRO_INFRARED + BLANCO_INFRARED)/2)
      return true;      // Negro -> Limite del tatami
  else 
      return false;
  
}

bool detecta_luz (int lrd_value){
  if (lrd_value < (LUZ_LDR  + AMBIENTE_LDR)/2)
      return true;      
  else 
      return false;
  
}


//*************************************************************************************************************
//*************************************************************************************************************
//*************************************************************************************************************


void sigue_luz(){
  int detec = 0;
  detec = 0;
  delay(5);
  Serial.println("LDRIzd      LDRDer ");
  Serial.print(LDRLeft);  
  Serial.print("   |     ");
  Serial.print(LDRRight); 
  Serial.println(" ");
  
  LDRRight = analogRead(pinLDRRight);
  LDRLeft = analogRead(pinLDRLeft);
  if (detecta_luz(LDRRight))
    detec +=1;
  if (detecta_luz(LDRLeft))
    detec +=2;
    
  if (detec == 1){  // Sendor derecho
    tubot.dcha(50);
    delay(50);
  }
  else if (detec == 2){  //Sendor izdo
    tubot.izda(50);
    delay(50);
  }
  else if (detec == 3){ // Ambos
    tubot.recto (100);
    delay(100);
  }
  else {
    tubot.para();
  }
  
  
}


void stay_in_tatami(){
  int detec = 0;
  detec = 0;
  delay(50);
  infraredRight = analogRead(pinInfraredRight);
  infraredLeft = analogRead(pinInfraredLeft);
  
  if (detecta_limite(infraredRight))
    detec +=1;
  if (detecta_limite(infraredLeft))
    detec +=2;
    
  if (detec == 1){  // Sendor derecho
    tubot.recto (-50);
    delay(500);
    tubot.izda(50);
    delay(300);
    tubot.para ();
  }
  else if (detec == 2){
    tubot.recto (-50);
    delay(500);
    tubot.dcha(30);
    delay(500);   
    tubot.para();
  }
  else if (detec == 3){
    tubot.recto (-30);
    delay(1000);
    tubot.dcha(50);
    delay(1000);
  }
  else {
     strike();
  }
  }

void detect_mov(){
  long rand;
  distance = Dist.getDistanceCentimeter();
    
   if (distance > 30) {    // To change direction
       randomSeed(distance);
       rand = random(0, 10);
   }
   if (distance > 10){
      tubot.recto(30);
      delay(100);
   }
   else {
     rand = random(0, 10);
      tubot.recto(-20);
     delay(600);
     if (rand > 5){
      tubot.dcha(40);
     }
    else {
     tubot.izda(40);
    } 
    delay(400);
   }
  
}
void strike(){
  long rand1, rand2;
  
  delay(20);
  distance = Dist.getDistanceCentimeter();
   rand2 = random(0, 10);
   rand1 = random(0, 10);
   if (distance < 15) {    // Si detectamos al otro robot
       randomSeed(distance);
       rand1 = random(0, 10);
       tubot.recto(100);
       delay(100);
   }
   else {
     if (rand1 > 5) {
       tubot.dcha(40);
       delay(500+rand2*100);
       tubot.recto(30);
       delay(200);
     }
     else {
       tubot.izda(40);
       delay(500 + rand2*100);
      tubot.recto(30);
       delay(200);
   
     }
  }
}

void check_function(){ {
  distance = Dist.getDistanceCentimeter();
  delay(100);
  button = digitalRead(pinButton);
  potenciometer = analogRead(pinPotenciometer);
  infraredRight = analogRead(pinInfraredRight);
  infraredLeft = analogRead(pinInfraredLeft);
  LDRRight = analogRead(pinLDRRight);
  LDRLeft = analogRead(pinLDRLeft);
  
  Serial.println("Distancia      Pulsador      Potenciometro      SensorIzd      SensorDer      LDRIzd      LDRDer      VelMotIzd       VelMotDer      CalMotorIzd      CalMotorDer ");
 
  Serial.print(distance);
  Serial.print("          |        ");
  Serial.print(button);  
  Serial.print("    |         ");
  Serial.print(potenciometer);  
  Serial.print("      |         ");
  Serial.print(infraredLeft);  
  Serial.print("   |     ");
  Serial.print(infraredRight); 
  Serial.print("    |    ");
  Serial.print(LDRLeft);  
  Serial.print("   |     ");
  Serial.print(LDRRight);  
  Serial.print("      |      ");
  Serial.print(tubot.motorIzda.getSpeed()); 
  Serial.print("       |        ");
  Serial.print(tubot.motorDcha.getSpeed()); 
  Serial.print("       |        ");
  Serial.print(tubot.motorIzda.getZero());  
  Serial.print("       |        ");
  Serial.print(tubot.motorDcha.getZero());  

  Serial.println(" ");
  
if (Serial.available() > 0) 
  {
     incomingByte = Serial.read();
     switch (incomingByte)
     {
       
       //------------> Right motor <-------
       case 'l':
   
         tubot.motorDcha.setZero( tubot.motorDcha.getZero() + 2);
         tubot.motorDcha.setSpeed(0);
         break;
         
       case 'j':
         tubot.motorDcha.setZero( tubot.motorDcha.getZero() - 2);
         tubot.motorDcha.setSpeed(0);
         break;
 
      case 'i':
         
         tubot.motorDcha.setSpeed(-(tubot.motorDcha.getSpeed() + 2));
         break;
         
       case 'k':
         tubot.motorDcha.setSpeed(-(tubot.motorDcha.getSpeed() - 2));
         break;
         
         //------------> Left motor <-------
       case 'd':
         tubot.motorIzda.setZero( tubot.motorIzda.getZero() + 2);
         tubot.motorIzda.setSpeed(0);
         break;
         
       case 'a':
         tubot.motorIzda.setZero( tubot.motorIzda.getZero() - 2);
         tubot.motorIzda.setSpeed(0);
         break;         

       case 'w':
         tubot.motorIzda.setSpeed(tubot.motorIzda.getSpeed() + 2);
         break;
         
       case 's':
         tubot.motorIzda.setSpeed(tubot.motorIzda.getSpeed() - 2);
         break;
         

        //------------> General movs <-------------
       case 't':
         tubot.recto(50);
         break;
         
       case 'g':
         tubot.para();
         break;
         
       case 'f':
        tubot.izda(50);
         break;
         
       case 'h':
         tubot.dcha(50);
         break;

         //---------------> LED <-------------------
         
       case 'v':
         digitalWrite(pinLed, HIGH);
         break;
       
       case 'b':
         digitalWrite(pinLed, LOW);
         break;

     }  
  } 
    }
  }
  
void sigueLinea(){
  int detec = 0;
  detec = 0;
  delay(50);
  Serial.println("SensorIzd      SensorDer ");
  Serial.print(infraredLeft);  
  Serial.print("   |     ");
  Serial.print(infraredRight); 

  Serial.println(" ");
  tubot.recto (100);
  infraredRight = analogRead(pinInfraredRight);
  infraredLeft = analogRead(pinInfraredLeft);
  if (detecta_limite(infraredRight))
    detec +=1;
  if (detecta_limite(infraredLeft))
    detec +=2;
  if (detec == 1){  // Sensor derecho
    tubot.dcha(30);
    delay(5);
  }
  else if (detec == 2){
     tubot.izda(30);
    delay(5);
  }
  else{
   tubot.recto(30);
  delay(10); 
  }
  
  }
  
  
  void ejemplo_motores (){
    
    // 1) Creamos los motores
    MotorTubot motorIzda;
    MotorTubot motorDcha;
    
    // 2) Asociamos a cada motor su pin de la placa.
    motorIzda.begin(9);    
    motorDcha.begin(10);   
    
    // 3) Establecemos el 0 de los motores
    motorIzda.setZero(1300);  
    motorDcha.setZero(1270); 
    
    // 4) Damos velocidad a los motores (-100 a 100) 
    motorIzda.setSpeed(60);  
    motorDcha.setSpeed(-30); 
    
  }
    

