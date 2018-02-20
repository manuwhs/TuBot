



int pinPotenciometer = A0;
int potenciometer;

void setup(){
  Serial.begin(19200); // Configuramos comunicacion serie
}

void loop()
{
  float calculo;
  potenciometer = analogRead(pinPotenciometer);
  calculo = (float)potenciometer*(5.0/1023);
  Serial.println("Potenciometro ");
  Serial.print(calculo);
  Serial.println("\n");
  delay(100);
}
  
