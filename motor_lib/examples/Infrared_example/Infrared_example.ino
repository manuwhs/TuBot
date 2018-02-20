
// Limites de los sensores
#define NEGRO_INFRARED 110
#define BLANCO_INFRARED  930
// Pines de los sensores
int pinInfraredRight = A1;
int pinInfraredLeft =  A2;
// Variables donde se guarda el valor de los sensores
int infraredRight;     
int infraredLeft;       

void setup(){
  Serial.begin(19200); // Configuramos comunicacion serie
}
void loop(){
   delay(200);
  // Leemos valor de los sensores.
  infraredRight = analogRead(pinInfraredRight);
  infraredLeft = analogRead(pinInfraredLeft);
 
 // Imprimimos el valor de los sensores
  Serial.println("SensorIzd      SensorDer  ");
  Serial.print(infraredLeft);  
  Serial.print("   |     ");
  Serial.println(infraredRight); 
}

/* Funcion que umbraliza la deteccion */
bool detecta_limite (int infraredValue){
  if (infraredValue < (NEGRO_INFRARED + BLANCO_INFRARED)/2)
      return true;      // Negro -> Limite del tatami
  else 
      return false;
  
}



