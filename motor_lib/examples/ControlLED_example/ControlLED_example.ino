/* Con este ejemplo podemos encender y apagar un LED puesto en el pin 12
mediante el teclado */

int pinLed  =          13;
int incomingByte = 0;
void setup(){
  Serial.begin(19200); 
  pinMode(pinLed, OUTPUT);     
}
void loop(){
    delay(200);
    // Leemos la información enviada por la comunicación serie.
    incomingByte = Serial.read();
    switch (incomingByte){  // Actuamos en función del valor de esta variable
         case 'v':        // Si hemos recibido el caracter 'v'
          digitalWrite(pinLed, HIGH);
         break;
           
         case 'b':     // Si hemos recibido el caracter 'b'
          digitalWrite(pinLed, LOW);
         break;
    }
}


