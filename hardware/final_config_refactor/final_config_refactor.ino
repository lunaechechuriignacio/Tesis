#include <WiFi.h>
#include <WiFiMulti.h>
#include <millisDelay.h>
#include <FirebaseESP32.h>

#define LED 2  // esto prueba que esta funcionando el sensor. Enciende el led de la placa esp32 BORRAR
#define FIREBASE_HOST "test-bdd-5f5f7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HKXQvDUpyBepZpCVXQ0XRTqFsh9gmULP4cpRWU1n"

WiFiMulti wifiMulti;
FirebaseData fbdo;

const uint32_t waitTimeWifi = 5000;
const int pir_sensor = 19;  // el numero de pin del esp32 conectado al sensor pir
const int relay_1 = 14;     // el numero de pin del esp32 conectado relay
const int relay_2 = 27;     // el numero de pin del esp32 conectado relay
const int relay_3 = 26;     // el numero de pin del esp32 conectado relay
const int relay_4 = 25;     // el numero de pin del esp32 conectado relay
const int relay_5 = 33;     // el numero de pin del esp32 conectado relay
const int relay_6 = 32;     // el numero de pin del esp32 conectado relay
const int relay_7 = 16;     // el numero de pin del esp32 conectado relay
const int relay_8 = 17;     // el numero de pin del esp32 conectado relay
int statusRelay1 = 1;

int currentStatusPirSensor = LOW;   // estado actual del pin
int previousStatusPirSensor = LOW;  // estado anterior del pin
int pirSensorAutomatic = 0;
millisDelay pirSensorDelay;  // defino la variable de tiempo para el sensor pir

void setModeAllRelays() {  // setea los pines del  ESP32 en modo salida para accionar los relays
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
  pinMode(relay_8, OUTPUT);
}

void setOffAllRelays() {
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, LOW);
  digitalWrite(relay_5, LOW);
  digitalWrite(relay_6, LOW);
  digitalWrite(relay_7, LOW);
  digitalWrite(relay_8, LOW);
}

void setModePirSensor() {
  pinMode(pir_sensor, INPUT);  // setea el pin del  ESP32 en modo entrada para leer los datos del sensor pir
}

void readStatusPirSensor() {
  previousStatusPirSensor = currentStatusPirSensor;  //guarda el estado anterior que se encontraba el sensor
  currentStatusPirSensor = digitalRead(pir_sensor);  // lee el estado actual del sensor

  if (previousStatusPirSensor == LOW && currentStatusPirSensor == HIGH) {  // el estado pasa de LOW -> HIGH ---DETECTA MOVIMIENTO
    Firebase.getInt(fbdo, "/pir_sensor/time_seconds");
    pirSensorDelay.start(fbdo.intData()*1000);  // asigno el tiempo que va a estar encendio  el relay, es customizable por el usuario se pasa COMO PARAMETRO DESDE LA APLICACION
    digitalWrite(LED, HIGH);                                               // esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
    Serial.println("MOVIMIENTO DETECTADO!");                               // BORRAR
    digitalWrite(relay_1, 0);                                              // ENCIENDO EL RELAY 1
    statusRelay1 = 0;
  } else if (pirSensorDelay.justFinished()) {
    digitalWrite(LED, LOW);  //BORRAR SOLO DE PRUEBA
    Serial.println("MOVIMIENTO NO DETECTADO");
    digitalWrite(relay_1, 1);  // APAGO EL RELAY 1
    statusRelay1 = 1;
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

int getPinRelayByNumber(int relay_number) {
  int pinRelay = 0;
  switch (relay_number) {
    case 1:
      pinRelay = relay_1;
      break;
    case 2:
      pinRelay = relay_2;
      break;
    case 3:
      pinRelay = relay_3;
      break;
    case 4:
      pinRelay = relay_4;
      break;
    case 5:
      pinRelay = relay_5;
      break;
    case 6:
      pinRelay = relay_6;
      break;
    case 7:
      pinRelay = relay_7;
      break;
    case 8:
      pinRelay = relay_8;
      break;
    default:
      break;
  }

  return pinRelay;
}

void getStatusRelay(int relay_number) {
  if (Firebase.getInt(fbdo, "/relays/relay_" + (String)(relay_number))) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.intData());
    digitalWrite(getPinRelayByNumber(relay_number), fbdo.intData());
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);  // es para que el sensor PIR se estabilice con el ambiente

  setModePirSensor();
  setModeAllRelays();

  pinMode(LED, OUTPUT);  // esto prueba que esta funcionando el sensor enciende el led de la placa esp32 BORRAR
  setOffAllRelays();

  connectWifi();
  connectFirebase();
}

void loop() {
  verifyConnectionWifi();

  getStatusRelay(2);
  getStatusRelay(3);
  getStatusRelay(4);
  getStatusRelay(5);
  getStatusRelay(6);
  getStatusRelay(7);
  getStatusRelay(8);
 
  updatePirSensorAutomatic();
  if (pirSensorAutomatic == 0) {
    readStatusPirSensor();
    Firebase.setInt(fbdo, "/relays/relay_1", statusRelay1);
  } else {
    getStatusRelay(1);
  }
}