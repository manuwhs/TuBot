
// Limites de los sensores
#define LUZ_LDR          100
#define AMBIENTE_LDR     800

// Pines de los sensores
int pinLDRRight =      A3;
int pinLDRLeft =       A4;
// Variables donde se guarda el valor de los sensores
int LDRRight;         
int LDRLeft;

void setup(){
  Serial.begin(19200);  // Configuramos comunicacion serie
}

void loop(){
  delay(200);
  // Leemos el valor de los sensores
  LDRRight = analogRead(pinLDRRight);
  LDRLeft = analogRead(pinLDRLeft);
  
  // Imprimimos el valor de los sensores
  Serial.println("LDRIzd      LDRDer  ");
  Serial.print(LDRLeft);  
  Serial.print("   |     ");
  Serial.println(LDRRight); 
  
}


/* Funcion que umbraliza la deteccion */
bool detecta_luz (int lrd_value){
  if (lrd_value < (LUZ_LDR  + AMBIENTE_LDR)/2)
      return true;      // Negro -> Limite del tatami
  else 
      return false;
  
}


