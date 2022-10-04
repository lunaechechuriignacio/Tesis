const int relay_0 = 14;
const int relay_1 = 27;
const int relay_2 = 26;
const int relay_3 = 25;
const int relay_4 = 33;
const int relay_5 = 32;
const int relay_6 = 16;
const int relay_7 = 17;

void setup() {
  pinMode(relay_0, OUTPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);
}

void loop() {
  digitalWrite(relay_0, LOW);
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);
  delay(5000);
  digitalWrite(relay_0, LOW);
  digitalWrite(relay_1, LOW);
  digitalWrite(relay_2, LOW);
  digitalWrite(relay_3, LOW);
  digitalWrite(relay_4, LOW);
  digitalWrite(relay_5, LOW);
  digitalWrite(relay_6, LOW);
  digitalWrite(relay_7, LOW);
  delay(5000);
}