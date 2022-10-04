

#define LED 2
const int PIN_TO_SENSOR =19; 
int pinStateCurrent   = LOW;  
int pinStatePrevious  = LOW;  

void setup() {
  Serial.begin(115200);            
  pinMode(LED,OUTPUT);
  pinMode(PIN_TO_SENSOR, INPUT); 
}

void loop() {
   
  pinStatePrevious = pinStateCurrent; 
  pinStateCurrent = digitalRead(PIN_TO_SENSOR);   
  Serial.println(pinStateCurrent);
    Serial.println(pinStatePrevious);
    
  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {   
    
    Serial.println("Motion detected!");
     delay(30);
    digitalWrite(LED,HIGH);
   
  }
  else
  if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {   
    Serial.println("Motion stopped!");
    delay(50);
     digitalWrite(LED,LOW);
    
  }
}
