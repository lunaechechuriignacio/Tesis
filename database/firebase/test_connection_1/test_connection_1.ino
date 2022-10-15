#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "JUANIBIANCA"
#define WIFI_PASSWORD "00429191276"

#define FIREBASE_HOST "prueba-conexion-4396c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBVdr6FlCRrh2rhpBn698VxtJJwrIF1b1s"

FirebaseData fbdo;
const int relay1 = 14;
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
void setup() {
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, 0);
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
}