/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-motion-sensor
 */
#define LED 2
const int PIN_TO_SENSOR =19; // GIOP19 pin connected to OUTPUT pin of sensor
int pinStateCurrent   = LOW;  // current state of pin
int pinStatePrevious  = LOW;  // previous state of pin

void setup() {
  Serial.begin(115200);            // initialize serial
  pinMode(LED,OUTPUT);
  pinMode(PIN_TO_SENSOR, INPUT); // set ESP32 pin to input mode to read value from OUTPUT pin of sensor
}

void loop() {
   
  pinStatePrevious = pinStateCurrent; // store old state
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state
  Serial.println(pinStateCurrent);
    Serial.println(pinStatePrevious);
    
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
    
    Serial.println("Motion detected!");
     delay(30);
    digitalWrite(LED,HIGH);
    // TODO: turn on alarm, light or activate a device ... here
  }
  else
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    delay(50);
     digitalWrite(LED,LOW);
    // TODO: turn off alarm, light or deactivate a device ... here
  }
}
