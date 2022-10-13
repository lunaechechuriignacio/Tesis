#define LED 2  /// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
#include <WiFi.h>
#include <WiFiMulti.h>
#include <millisDelay.h>
#include <FirebaseESP32.h>

#define FIREBASE_HOST "prueba-conexion-4396c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBVdr6FlCRrh2rhpBn698VxtJJwrIF1b1s"

WiFiMulti wifiMulti;
FirebaseData fbdo;

const uint32_t TiempoEsperaWifi = 5000;
const int pirConexion = 19;  // el numero de pin del esp32 conectado al sensor Pir
const int relay1 = 14;       // el numero de pin del esp32 conectado relay
const int relay2 = 27;       // el numero de pin del esp32 conectado relay
const int relay3 = 26;       // el numero de pin del esp32 conectado relay
const int relay4 = 25;       // el numero de pin del esp32 conectado relay
const int relay5 = 33;       // el numero de pin del esp32 conectado relay
const int relay6 = 32;       // el numero de pin del esp32 conectado relay
const int relay7 = 16;       // el numero de pin del esp32 conectado relay
const int relay8 = 17;       // el numero de pin del esp32 conectado relay
String estadoRele1 = "1";

int pirEstadoActual = LOW;  // estado actual del pin
int pirEstadoPrevio = LOW;  // estado anterior del pin
int pirAutomatico = 0;
millisDelay pirDelay;  // defino la variable de tiempo para el sensor pir

void setPinRelayrModo() {  // setea los pines del  ESP32 en modo salida para accionar los relay
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
}
void setOffAllRelay() {

  digitalWrite(relay1, 0);
  digitalWrite(relay2, 0);
  digitalWrite(relay3, 0);
  digitalWrite(relay4, 0);
  digitalWrite(relay5, 0);
  digitalWrite(relay6, 0);
  digitalWrite(relay7, 0);
  digitalWrite(relay8, 0);
}

int getEstadoSensorPirActual() {
  return pirEstadoActual;
}
void setEstadoSensorPirActual(int estado) {
  pirEstadoActual = estado;
}
void setPinPirModo() {
  pinMode(pirConexion, INPUT);  // setea el pin del  ESP32 en modo entrada para leer los datos del sensor pir
}

void leerEstadoSensorPir() {

  pirEstadoPrevio = pirEstadoActual;                   //guarda el estado anterior que se encontraba el sensor
  setEstadoSensorPirActual(digitalRead(pirConexion));  // lee el estado actual del sensor

  if (pirEstadoPrevio == LOW && pirEstadoActual == HIGH) {  // el estado pasa de LOW -> HIGH ---DETECTA MOVIMIENTO

    pirDelay.start(20000);                    // asigno el tiempo que va a estar encendio  el relay, es customizable por el usuario VER COMO PASARLO COMO PARAMETRO DESDE LA APLICACION
    digitalWrite(LED, HIGH);                  /// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
    Serial.println("MoVIMIENTO DETECTADO!");  //BORRAR
    digitalWrite(relay1, 0);                  // ENCIENDO EL RELAY 1
    estadoRele1 = "0";

  } else if (pirDelay.justFinished()) {
    digitalWrite(LED, LOW);  //BORRAR SOLO DE PRUEBA
    Serial.println("MOVIMIENTO NO DETECTADO");
    digitalWrite(relay1, 1);  // APAGO EL RELAY 1
    estadoRele1 = "1";
  }
}

void conexionFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}
void conexionWifi() {
  Serial.println("\nIniciando multi Wifi");

  wifiMulti.addAP("ARGENFARMA-CAMARA", "juansalierno2016");
  wifiMulti.addAP("JUANIBIANCA", "00429191276");  // VER COMO PASAR COMO PARAMETRO DESDE LA APLICACION
  wifiMulti.addAP("ssid_3", "contrasenna_3");

  WiFi.mode(WIFI_STA);
  Serial.print("Conectando a Wifi ..");
  while (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println(".. Conectado");
  Serial.print("SSID:");
  Serial.print(WiFi.SSID());
  Serial.print(" ID:");
  Serial.println(WiFi.localIP());
}

void ActualizarWifi() {
  if (wifiMulti.run(TiempoEsperaWifi) != WL_CONNECTED) {
    Serial.println("No conectado a Wifi!");
  }
}

void getEstadoConexionWifi() {
  ActualizarWifi();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Codigo con Wifi");
  } else {
    Serial.println("Codigo sin Wifi");
  }
  delay(1000);
}


void getEstadoPirAutomatico() {

  if (Firebase.getString(fbdo, "/pirAutomatico")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    pirAutomatico = fbdo.stringData().toInt();
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_1() {

  if (Firebase.getString(fbdo, "/relay1")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay1, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}

void getEstadoRele_2() {

  if (Firebase.getString(fbdo, "/relay2")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay2, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_3() {

  if (Firebase.getString(fbdo, "/relay3")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay3, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_4() {

  if (Firebase.getString(fbdo, "/relay4")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay4, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_5() {

  if (Firebase.getString(fbdo, "/relay5")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay5, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_6() {

  if (Firebase.getString(fbdo, "/relay6")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay6, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void getEstadoRele_7() {

  if (Firebase.getString(fbdo, "/relay7")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay7, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}

void getEstadoRele_8() {

  if (Firebase.getString(fbdo, "/relay8")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    digitalWrite(relay8, fbdo.stringData().toInt());
  } else {
    Serial.print("Error in getString, ");
    Serial.println(fbdo.errorReason());
  }
}
void setup() {
  Serial.begin(115200);
  delay(300);  // es para que el sensor PIR se estabilice con el ambiente
  setPinPirModo();
  setPinRelayrModo();
  conexionWifi();
  pinMode(LED, OUTPUT);  /// esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
  setOffAllRelay();
  conexionFirebase();
}

void loop() {
  getEstadoConexionWifi();

  getEstadoRele_2();
  getEstadoRele_3();
  getEstadoRele_4();
  getEstadoRele_5();
  getEstadoRele_6();
  getEstadoRele_5();
  getEstadoRele_6();
  getEstadoRele_7();
  getEstadoRele_8();

  getEstadoPirAutomatico();
  if (pirAutomatico == 0) {
    leerEstadoSensorPir();
    Firebase.setString(fbdo, "/relay1", estadoRele1);
  } else
    getEstadoRele_1();
}