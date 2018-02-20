/* Este programa lee la distancia obtenida con el SRF04 y la imprime en pantalla*/
#include <DistanceSRF04.h> // Incluímos librería del SRF04
// Pines del SRF04
int pinEco  =           2;
int pinTrigger =        3;
// Variables para el control del sensor
DistanceSRF04 Dist;
int distance;

void setup(){
  Serial.begin(19200);
  // Configuramos los pines del sensor.
  Dist.begin(pinEco,pinTrigger);
}

void loop(){
  delay(200);
  // Guardamos la distancia del sensor en la variable
  distance = Dist.getDistanceCentimeter();
  // Enviamos el valor de la distancia por la comunicación serie
  Serial.print("Distancia  ");
  Serial.print(distance);
  Serial.println("cm"); 
}


