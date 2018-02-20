/* Este programa lee el estado de un boton situado en el pin 4 y lo imprime en 
el Monitor Serial */
int pinButton = 4;
int led = 13;
int button;  // Variable donde se guarda el estado del botón
void setup(){
  //Configuración de la comunicación serie.
 
  //Establecemos el pin del botón como entrada.
  pinMode(pinButton, INPUT);  
  pinMode(led, OUTPUT);

}

void loop(){
    delay(200);
    // Leemos el valor digital del botón (0 o 1).
    button = digitalRead(pinButton);
    if(button==0)
           digitalWrite(led, HIGH);
    else
           digitalWrite(led, LOW);
    
}


