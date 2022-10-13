#include <millisDelay.h>

#define LED 2
const int PIN_TO_SENSOR =19; 
int pinStateCurrent   = LOW;  
int pinStatePrevious  = LOW; 
unsigned long currentTime ; 
millisDelay pirDelay; 
const int relay_0 = 14;

void setup() {
  Serial.begin(115200);            
  pinMode(LED,OUTPUT);
  pinMode(PIN_TO_SENSOR, INPUT); 
 // pinMode(relay_0, OUTPUT);
}

void detectarMovimiento() {
  pinStatePrevious = pinStateCurrent; 
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   
  // Serial.println(pinStateCurrent);
  // Serial.println(pinStatePrevious);
    
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   
    pirDelay.start(20000);
    Serial.println("Motion detected!");
    
    digitalWrite(LED,HIGH);
  } else if (/*pinStatePrevious == HIGH && pinStateCurrent == LOW &&*/ pirDelay.justFinished()) {   
    Serial.println("Motion stopped!");
    digitalWrite(LED,LOW);
  }
}

void loop() {
   detectarMovimiento();
}