
#define LED 2/// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR

const int pirConexion = 19; // el numero de pin del esp32 conectado al sensor Pir
const int relay_0 = 14; // el numero de pin del esp32 conectado relay
const int relay_1 = 27;// el numero de pin del esp32 conectado relay
const int relay_2 = 26;// el numero de pin del esp32 conectado relay
const int relay_3 = 25;// el numero de pin del esp32 conectado relay
const int relay_4 = 33;// el numero de pin del esp32 conectado relay
const int relay_5 = 32;// el numero de pin del esp32 conectado relay
const int relay_6 = 16;// el numero de pin del esp32 conectado relay
const int relay_7 = 17;// el numero de pin del esp32 conectado relay

int pirEstadoActual   = LOW;  // estado actual del pin
int pirEstadoPrevio  = LOW;  // estado anterior del pin

int getEstadoSensorPirActual() {
  return pirEstadoActual;
}
void setEstadoSensorPirActual(int estado) {
  pirEstadoActual = estado;
}
void setPinPirModo() {
  pinMode(pirConexion, INPUT); // setea el pin del  ESP32 en modo entrada para leer los datos del sensor pir
}

void leerEstadoSensorPir() {

 

  pirEstadoPrevio = pirEstadoActual; //guarda el estado anterior que se encontraba el sensor
  setEstadoSensorPirActual( digitalRead(pirConexion));   // lee el estado actual del sensor

  if (pirEstadoPrevio == LOW && pirEstadoActual == HIGH) {   // el estado pasa de LOW -> HIGH ---DETECTA MOVIMIENTO

    delay(50); digitalWrite(LED, HIGH); /// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
    // ENCENDER RELAY - HACER UN TIMER
  }
  else if (pirEstadoPrevio == HIGH && pirEstadoActual == LOW) {
    digitalWrite(LED, LOW);
    // APAGAR LUCES SI SE CUMPLE TAMBIEN LA CANDICION DEL TIMER
  }

}

void setPinRelayrModo() { // setea los pines del  ESP32 en modo salida para accionar los relay
  pinMode(relay_0, OUTPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
}

void setOnRelay_1( ) {
  digitalWrite(relay_0, HIGH);
}
void setOnRelay_2( ) {
  digitalWrite(relay_1, HIGH);
}
void setOnRelay_3( ) {
  digitalWrite(relay_2, HIGH);
}
void setOnRelay_4( ) {
  digitalWrite(relay_3, HIGH);
}
void setOnRelay_5( ) {
  digitalWrite(relay_4, HIGH);
}
void setOnRelay_6( ) {
  digitalWrite(relay_5, HIGH);
}
void setOnRelay_7( ) {
  digitalWrite(relay_6, HIGH);
}
void setOnRelay_8( ) {
  digitalWrite(relay_7, HIGH);
}
void setOFFRelay_1( ) {
  digitalWrite(relay_0, LOW);
}
void setOFFRelay_2( ) {
  digitalWrite(relay_1, LOW);
}
void setOFFRelay_3( ) {
  digitalWrite(relay_2, LOW);
}
void setOFFRelay_4( ) {
  digitalWrite(relay_3, LOW);
}
void setOFFRelay_5( ) {
  digitalWrite(relay_4, LOW);
}
void setOFFRelay_6( ) {
  digitalWrite(relay_5, LOW);
}
void setOFFRelay_7( ) {
  digitalWrite(relay_6, LOW);
}
void setOFFRelay_8( ) {
  digitalWrite(relay_7, LOW);
}

void conexionWifi(){
  ///////////////////////////////////////////////////////////////////////////////

  }
void setup() {
  Serial.begin(115200);
  delay(300); // es para que el sensor PIR se estabilice con el ambiente
  setPinPirModo();
  setPinRelayrModo();
  pinMode(LED, OUTPUT); /// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR

}
void loop() {

  leerEstadoSensorPir();
}
