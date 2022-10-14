#include <WiFi.h>
#include <FirebaseESP32.h>

// Credenciales WiFi (del celular)
#define WIFI_SSID "GonzaloNahuelDP"
#define WIFI_PASSWORD "*GNahuel1993*"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://prueba-conexion-4396c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "omVcN33FXeEVJ0w2NvGYaVhuS9SOY0fSkytJTtg7" // authorization, key, token

// Firebase Data object
FirebaseData firebase_data;

// Ruta principal
String main_path = "/test";
bool iterate = true;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al WiFi");
  Serial.println();

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  while(iterate)
  {
    // leer datos:

    // integer
    Firebase.getInt(firebase_data, main_path + "/number");
    delay(250);
    Serial.print("/test/number: ");
    Serial.println(firebase_data.intData());

    // string
    Firebase.getString(firebase_data, main_path + "/word");
    delay(250);
    Serial.print("/test/word: ");
    Serial.println(firebase_data.stringData());

    iterate = false;
    Firebase.end(firebase_data);
  }
}
