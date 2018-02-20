/* Este programa hace parpadear un led situado en el pin 12 */
int pinLed  =          13;

void setup(){
  // Establecemos el pin del LED como salida
  pinMode(pinLed, OUTPUT);     
}

void loop(){
     delay(500);
     digitalWrite(pinLed, HIGH);
     delay(500);
     digitalWrite(pinLed, LOW);
}


  
    

