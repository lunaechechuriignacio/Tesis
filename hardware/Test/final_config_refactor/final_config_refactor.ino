#include <WiFi.h>
#include <WiFiMulti.h>
#include <millisDelay.h>
#include <FirebaseESP32.h>
#include <relay.h>
#define LED 2  // esto prueba que esta funcionando el sensor. Enciende el led de la placa esp32 BORRAR
#define FIREBASE_HOST "test-bdd-5f5f7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HKXQvDUpyBepZpCVXQ0XRTqFsh9gmULP4cpRWU1n"

WiFiMulti wifiMulti;
FirebaseData fbdo;

const uint32_t waitTimeWifi = 5000;
const int pir_sensor = 19;

relay relay_1;
relay relay_2;
relay relay_3;
relay relay_4;
relay relay_5;
relay relay_6;
relay relay_7;
relay relay_8;
int statusRelay1 = 1;

int currentStatusPirSensor = LOW;   // estado actual del pin
int previousStatusPirSensor = LOW;  // estado anterior del pin
int pirSensorAutomatic = 0;
millisDelay pirSensorDelay;  // defino la variable de tiempo para el sensor pir

void setPinRelay() {
  relay_1.setPort(14);
  relay_2.setPort(27);
  relay_3.setPort(26);
  relay_4.setPort(25);
  relay_5.setPort(33);
  relay_6.setPort(32);
  relay_7.setPort(16);
  relay_8.setPort(17);
}

void setNumberRelay() {
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

void setOffAllRelays() {
  digitalWrite(relay_1.getPort(), LOW);
  digitalWrite(relay_2.getPort(), LOW);
  digitalWrite(relay_3.getPort(), LOW);
  digitalWrite(relay_4.getPort(), LOW);
  digitalWrite(relay_5.getPort(), LOW);
  digitalWrite(relay_6.getPort(), LOW);
  digitalWrite(relay_7.getPort(), LOW);
  digitalWrite(relay_8.getPort(), LOW);
}

void setModePirSensor() {
  pinMode(pir_sensor, INPUT);  // setea el pin del  ESP32 en modo entrada para leer los datos del sensor pir
}

void readStatusPirSensor() {
  previousStatusPirSensor = currentStatusPirSensor;  //guarda el estado anterior que se encontraba el sensor
  currentStatusPirSensor = digitalRead(pir_sensor);  // lee el estado actual del sensor

  if (previousStatusPirSensor == LOW && currentStatusPirSensor == HIGH) {  // el estado pasa de LOW -> HIGH ---DETECTA MOVIMIENTO
    Firebase.getInt(fbdo, "/pir_sensor/time_seconds");
    pirSensorDelay.start(fbdo.intData() * 1000);  // asigno el tiempo que va a estar encendio  el relay, es customizable por el usuario se pasa COMO PARAMETRO DESDE LA APLICACION
    digitalWrite(LED, HIGH);                      // esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
    Serial.println("MOVIMIENTO DETECTADO!");      // BORRAR
    digitalWrite(relay_1.getPort(), 0);           // ENCIENDO EL RELAY 1
    relay_1.setStatus(0);
  } else if (pirSensorDelay.justFinished()) {
    digitalWrite(LED, LOW);  //BORRAR SOLO DE PRUEBA
    Serial.println("MOVIMIENTO NO DETECTADO");
    digitalWrite(relay_1.getPort(), 1);  // APAGO EL RELAY 1
    relay_1.setStatus(1);
  }
}

void connectWifi() {
  Serial.println("\nIniciando multi Wifi");

  // Nacho
  wifiMulti.addAP("ARGENFARMA-CAMARA", "juansalierno2016");
  wifiMulti.addAP("JUANIBIANCA", "00429191276");
  wifiMulti.addAP("ssid_3", "contrasenna_3");

  // Gonza
  // wifiMulti.addAP("Aorus", "Elsa220263");
  // wifiMulti.addAP("GonzaloNahuelDP", "*GNahuel1993*");

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
  delay(1000);
}

void connectFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void updatePirSensorAutomatic() {
  if (Firebase.getInt(fbdo, "/pir_sensor/automatic")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.intData());
    pirSensorAutomatic = fbdo.intData();
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}

void getStatusRelay(relay relay) {
  Serial.println("/relays/relay_" + (String)(relay.getNumber())+"/status");
  if (Firebase.getInt(fbdo, "/relays/relay_" + (String)(relay.getNumber())+"/status")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.intData());
    digitalWrite(relay.getPort(), fbdo.intData());  //////////////////////////////////////
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
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
  
  getStatusRelay(relay_2);
  getStatusRelay(relay_3);
  getStatusRelay(relay_4);
  getStatusRelay(relay_5);
  getStatusRelay(relay_6);
  getStatusRelay(relay_7);
  getStatusRelay(relay_8);

  updatePirSensorAutomatic();
  if (pirSensorAutomatic == 0) {
    readStatusPirSensor();
    Firebase.setInt(fbdo, "/relays/relay_1/status", relay_1.getStatus());
  } else {
    getStatusRelay(relay_1);
  }
}