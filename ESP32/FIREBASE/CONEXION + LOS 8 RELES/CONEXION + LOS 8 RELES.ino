#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "JUANIBIANCA"
#define WIFI_PASSWORD "00429191276"

#define FIREBASE_HOST "prueba-conexion-4396c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBVdr6FlCRrh2rhpBn698VxtJJwrIF1b1s"

FirebaseData fbdo;
const int relay1 = 14;
const int relay2 = 27;
const int relay3 = 26;
const int relay4 = 25;
const int relay5 = 33;
const int relay6 = 32;
const int relay7 = 16;
const int relay8 = 17;

void conexionFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
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
  pinMode(relay8, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  digitalWrite(relay8, 0);
  digitalWrite(relay1, 0);
  digitalWrite(relay2, 0);
  digitalWrite(relay3, 0);
  digitalWrite(relay4, 0);
  digitalWrite(relay5, 0);
  digitalWrite(relay6, 0);
  digitalWrite(relay7, 0);

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  conexionFirebase();
}

void loop() {

  getEstadoRele_1();
  getEstadoRele_2();
  getEstadoRele_3();
  getEstadoRele_4();
  getEstadoRele_5();
  getEstadoRele_6();
  getEstadoRele_5();
  getEstadoRele_6();
  getEstadoRele_7();
  getEstadoRele_8();
}