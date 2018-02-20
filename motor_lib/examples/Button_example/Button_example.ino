/* Este programa lee el estado de un boton situado en el pin 4 y lo imprime en 
el Monitor Serial */
int pinButton =         4;
int button;  // Variable donde se guarda el estado del botón
void setup(){
  //Configuración de la comunicación serie.
  Serial.begin(19200); 
  //Establecemos el pin del botón como entrada.
  pinMode(pinButton, INPUT);  

}

void loop(){
    delay(200);
    // Leemos el valor digital del botón (0 o 1).
    button = digitalRead(pinButton);
    // Imprimimos por pantalla el estado del botón.
    Serial.print("Valor boton: ");  
    Serial.println(button);  
}


