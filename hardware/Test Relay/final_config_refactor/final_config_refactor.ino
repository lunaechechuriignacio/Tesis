#include <WiFi.h>
#include <WiFiMulti.h>
#include <millisDelay.h>
#include <FirebaseESP32.h>
#include <Relay.h>
#include <Wire.h>
#include "RTClib.h"
#define LED 2  // esto prueba que esta funcionando el sensor. Enciende el led de la placa esp32 BORRAR
#define FIREBASE_HOST "test-bdd-5f5f7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HKXQvDUpyBepZpCVXQ0XRTqFsh9gmULP4cpRWU1n"

WiFiMulti wifiMulti;
FirebaseData fbdo;

const uint32_t waitTimeWifi = 5000;
const int pir_sensor = 19;

Relay relay_1;
Relay relay_2;
Relay relay_3;
Relay relay_4;
Relay relay_5;
Relay relay_6;
Relay relay_7;
Relay relay_8;
int statusRelay1 = 1;

int currentStatusPirSensor = LOW;   // estado actual del pin
int previousStatusPirSensor = LOW;  // estado anterior del pin
int pirSensorAutomatic = 0;
millisDelay pirSensorDelay;  // defino la variable de tiempo para el sensor pir

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"DOMINGO", "LUNES", "MARTES", "MIERCOLES", "JUEVES", "VIERNES", "SABADO"};

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
    // digitalWrite(relay_1.getPort(), 0);           // ENCIENDO EL RELAY 1
    relay_1.setStatus(0);
  } else if (pirSensorDelay.justFinished()) {
    digitalWrite(LED, LOW);  //BORRAR SOLO DE PRUEBA
    Serial.println("MOVIMIENTO NO DETECTADO");
    // digitalWrite(relay_1.getPort(), 1);  // APAGO EL RELAY 1
    relay_1.setStatus(1);
  }
  digitalWrite(relay_1.getPort(), relay_1.getStatus());
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

void getStatusRelay(Relay relay) {

  if (Firebase.getInt(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/status")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.intData());
    digitalWrite(relay.getPort(), fbdo.intData());  //////////////////////////////////////
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}

void getTimeRelay(Relay relay) {

  if (Firebase.getString(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/start_time")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    relay.setStartTime(fbdo.stringData());
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
  if (Firebase.getString(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/end_time")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.stringData());
    relay.setEndTime(fbdo.stringData());
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}
void getAutomaticRelay(Relay relay) {

  if (Firebase.getBool(fbdo, "/relays/relay_" + (String)(relay.getNumber()) + "/automatic")) {
    Serial.print("Get int data A success, str = ");
    Serial.println(fbdo.boolData());
    relay.setAutomatic( fbdo.boolData());  //////////////////////////////////////
  } else {
    Serial.print("Error in getInt, ");
    Serial.println(fbdo.errorReason());
  }
}

void getUpdateRelay(Relay relay) {
  getStatusRelay(relay);
  getTimeRelay(relay);
  getAutomaticRelay(relay);
}

void initRtc() {
  if (! rtc.begin()) {
    Serial.println("no se puede encontrar el  RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC perdio la energia,  se seteara el tiempo ahora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Si el RTC  perdido energía, establecerá en el RTC en la fecha y hora cuando se compiló este línea
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
  initRtc() ;
}

void loop() {
  verifyConnectionWifi();

  getUpdateRelay(relay_2);
  getUpdateRelay(relay_3);
  getUpdateRelay(relay_4);
  getUpdateRelay(relay_5);
  getUpdateRelay(relay_6);
  getUpdateRelay(relay_7);
  getUpdateRelay(relay_8);

  updatePirSensorAutomatic();
  if (pirSensorAutomatic == 0) {
    readStatusPirSensor();
    Firebase.setInt(fbdo, "/relays/relay_1/status", relay_1.getStatus());
  } else {
    getUpdateRelay(relay_1);
  }

  ////////////////////////////////////solo de prueba BORRRAR////////////////////


  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();


  Serial.print("Temperature: ");
  Serial.print(rtc.getTemperature());
  Serial.println(" C");

  Serial.println();
  ////////////////////////////////////solo de prueba BORRRAR////////////////////

}