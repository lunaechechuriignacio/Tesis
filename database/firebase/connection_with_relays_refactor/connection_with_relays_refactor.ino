#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "GonzaloNahuelDP"
#define WIFI_PASSWORD "*GNahuel1993*"

#define FIREBASE_HOST "test-bdd-5f5f7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "HKXQvDUpyBepZpCVXQ0XRTqFsh9gmULP4cpRWU1n"

FirebaseData fbdo;
const int relay_1 = 14;
const int relay_2 = 27;
const int relay_3 = 26;
const int relay_4 = 25;
const int relay_5 = 33;
const int relay_6 = 32;
const int relay_7 = 16;
const int relay_8 = 17;

void connectFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
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
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
  pinMode(relay_8, OUTPUT);

  digitalWrite(relay_1, 0);
  digitalWrite(relay_2, 0);
  digitalWrite(relay_3, 0);
  digitalWrite(relay_4, 0);
  digitalWrite(relay_5, 0);
  digitalWrite(relay_6, 0);
  digitalWrite(relay_7, 0);
  digitalWrite(relay_8, 0);

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

  connectFirebase();
}

void loop() {
  getStatusRelay(1);
  getStatusRelay(2);
  getStatusRelay(3);
  getStatusRelay(4);
  getStatusRelay(5);
  getStatusRelay(6);
  getStatusRelay(7);
  getStatusRelay(8);
  Serial.println();
  delay(100);
}