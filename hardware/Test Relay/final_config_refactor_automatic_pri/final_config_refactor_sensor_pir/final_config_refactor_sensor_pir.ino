#include <WiFi.h>
#include <WiFiMulti.h>
#include <millisDelay.h>
#include <FirebaseESP32.h>
#include <Relay.h>
#include <Wire.h>
#define LED 2  // esto prueba que esta funcionando el sensor. Enciende el led de la placa esp32 
#define FIREBASE_HOST "test-bdd-5f5f7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HKXQvDUpyBepZpCVXQ0XRTqFsh9gmULP4cpRWU1n"

WiFiMulti wifiMulti;
FirebaseData fbdo;

const uint32_t waitTimeWifi = 5000;// tiempo de conexion del WIFI
const int pir_sensor = 19;// asignacion del pin del sensro Pir

Relay relay_1;
Relay relay_2;
Relay relay_3;
Relay relay_4;
Relay relay_5;
Relay relay_6;
Relay relay_7;
Relay relay_8;


int currentStatusPirSensor = LOW;   // estado actual del pin
int previousStatusPirSensor = LOW;  // estado anterior del pin
bool enabledPir = false;//sensor pir si esta activo o no
millisDelay pirSensorDelay;  // defino la variable de tiempo para el sensor pir

void setPinRelay() {//se asigna el pin de conexion a los relays
  relay_1.setPort(14);
  relay_2.setPort(27);
  relay_3.setPort(26);
  relay_4.setPort(25);
  relay_5.setPort(33);
  relay_6.setPort(32);
  relay_7.setPort(16);
  relay_8.setPort(17);
}

void setNumberRelay() {//ASIGNA EL NUMERO A CADA RELAY
  relay_1.setNumber(1);
  relay_2.setNumber(2);
  relay_3.setNumber(3);
  relay_4.setNumber(4);
  relay_5.setNumber(5);
  relay_6.setNumber(6);
  relay_7.setNumber(7);
  relay_8.setNumber(8);
}

void setupRelay() {
  setPinRelay();
  setNumberRelay();
}

void setModeAllRelays() {  // setea los pines del  ESP32 en modo salida para accionar los relays
  pinMode(relay_1.getPort(), OUTPUT);
  pinMode(relay_2.getPort(), OUTPUT);
  pinMode(relay_3.getPort(), OUTPUT);
  pinMode(relay_4.getPort(), OUTPUT);
  pinMode(relay_5.getPort(), OUTPUT);
  pinMode(relay_6.getPort(), OUTPUT);
  pinMode(relay_7.getPort(), OUTPUT);
  pinMode(relay_8.getPort(), OUTPUT);
}

void setOffAllRelays() {//APAGA TODOS LOS RELAYS
  digitalWrite(relay_1.getPort(), LOW);
  digitalWrite(relay_2.getPort(), LOW);
  digitalWrite(relay_3.getPort(), LOW);
  digitalWrite(relay_4.getPort(), LOW);
  digitalWrite(relay_5.getPort(), LOW);
  digitalWrite(relay_6.getPort(), LOW);
  digitalWrite(relay_7.getPort(), LOW);
  digitalWrite(relay_8.getPort(), LOW);
}

void setModePirSensor() {// setea el pin del  ESP32 en modo entrada para leer los datos del sensor pir
  pinMode(pir_sensor, INPUT);  
}

void readStatusPirSensor() { // lee si el sensor Pir dectecto movimiento

  previousStatusPirSensor = currentStatusPirSensor;//guarda el estado anterior que se encontraba el sensor
  currentStatusPirSensor = digitalRead(pir_sensor);// lee el estado actual del sensor


  if (previousStatusPirSensor == LOW && currentStatusPirSensor == HIGH) {// el estado pasa de LOW -> HIGH ---DETECTA MOVIMIENTO

    Serial.println("Motion detected!");
    digitalWrite(LED, HIGH);  // esto prueba que esta funcionando el sensor enciende el led azul de la placa esp32  
    Firebase.getInt(fbdo, "/pir_sensor/time_seconds");// lee de la base de datos el tiempo asignado por el usuario
    pirSensorDelay.start(fbdo.intData() * 1000);  // asigno el tiempo que va a estar encendio  el relay, es customizable por el usuario se pasa COMO PARAMETRO DESDE LA APLICACION
  // se multiplica por 1000 porque esta en milisegundos
    enabledPir = true;                            
    Serial.println("MOVIMIENTO DETECTADO!");  // BORRAR

  } else if (pirSensorDelay.justFinished()) {
    Serial.println("MOVIMIENTO NO DETECTADO!");
    digitalWrite(LED, LOW);// esto prueba que esta funcionando el sensor apaga el led azul de la placa esp32 
    enabledPir = false;
  }
}

void writeDatabaseRelayStatus(Relay relay) {
  Firebase.setInt(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/status", relay.getStatus());
}
void connectWifi() {// conexion wifi
  Serial.println("\nIniciando multi Wifi");

  // Nacho
  wifiMulti.addAP("ARGENFARMA-CAMARA", "juansalierno2016");
  wifiMulti.addAP("JUANIBIANCA", "00429191276");
  wifiMulti.addAP("Nachox", "juanibianca");

   //Gonza
   wifiMulti.addAP("Aorus", "Elsa220263");
  wifiMulti.addAP("GonzaloNahuelDP", "*GNahuel1993*");

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ...");
  while (wifiMulti.run(waitTimeWifi) != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("... Conectado");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("ID: ");
  Serial.println(WiFi.localIP());
}

void updateWifi() {
  if (wifiMulti.run(waitTimeWifi) != WL_CONNECTED) {
    Serial.println("No conectado a Wifi!");
  }
}

void verifyConnectionWifi() {
  updateWifi();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Codigo con Wifi");
  } else {
    Serial.println("Codigo sin Wifi");
  }
 // delay(1000);
}

void connectFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void getStatusRelay(Relay relay) {//lee de la base de datos en que estado se encuentra el estado del sensor
  int status = 0;

  if (Firebase.getInt(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/status")) {
    status = fbdo.intData();
    relay.setStatus(status);// se asigna el relay el estado en que se encuentra segun la base de  datos
    if (status == 1)
      status = 0;
    else
      status = 1;
    digitalWrite(relay.getPort(), status);// activa o desactiva el relay segun el estado de la base de datos
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}

bool getAutomaticRelay(Relay relay) {//lee de la base de datos si esta activo el modo automatico
  bool automaticSensor = false;

  if (Firebase.getBool(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/automatic")) {
    automaticSensor = fbdo.boolData();
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
  return automaticSensor;
}

void getUpdateRelay(Relay relay) {
  relay.setAutomatic(getAutomaticRelay(relay));// setea en el relay el modo automatico TRUE/FALSE
  readStatusPirSensor();//lee si el sensor esta activo o inactivo
  if (relay.getAutomatic()) {// se esta en modo automatico
    if (enabledPir)//si esta activo el el sensor enciende el relay
      relay.setStatus(1);//activa el relay
    else
      relay.setStatus(0);//desactiva el relay

    writeDatabaseRelayStatus(relay);//modofica en la base de datos el estado del sensor segun su estado actual
  }
  getStatusRelay(relay);
}

void setup() {
  Serial.begin(115200);
  delay(300);  // es para que el sensor PIR se estabilice con el ambiente
  setupRelay();
  setModePirSensor();
  setModeAllRelays();

  pinMode(LED, OUTPUT);  // esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
  setOffAllRelays();

  connectWifi();
  connectFirebase();
}

void loop() {
  verifyConnectionWifi();
  getUpdateRelay(relay_1);
  getUpdateRelay(relay_2);
  getUpdateRelay(relay_3);
  getUpdateRelay(relay_4);
  getUpdateRelay(relay_5);
  getUpdateRelay(relay_6);
  getUpdateRelay(relay_7);
  getUpdateRelay(relay_8);
}