// para Windows 10 se deben instalar los drivers de la placa, ya que es probable que la misma no sea reconocida inmediatamente
// (chequear en "Administrador de dispositivos" de Windows)
// CP210x Universal Windows Driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads

#define LED 2

void setup() {
  //Serial.begin(115200); // velocidad de transmision (en baudios)
  //Serial.println("Hola Mundo!");
  //Serial.println("Esto es el setup.");

  pinMode(LED,OUTPUT); //set up pin mode
}

void loop() {
  //Serial.println("Esto es el loop.");
  //delay(2000); // espera de 2 segundos

  delay(1000); // espera de 1 segundo
  digitalWrite(LED,HIGH); // enciende el LED
  delay(1000); // espera de 1 segundo
  digitalWrite(LED,LOW); // apaga el LED
}
