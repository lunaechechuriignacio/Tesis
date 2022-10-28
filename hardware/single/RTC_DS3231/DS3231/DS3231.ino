#include <Wire.h>
#include "RTClib.h"
//////////// instalar la libreria RTClib//////////////////

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"DOMINGO", "LUNES", "MARTES", "MIERCOLES", "JUEVES", "VIERNES", "SABADO"};

void setup() {
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("no se puede encontrar el  RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC perdio la energia,  se seteara el tiempo ahora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Si el RTC  perdido energía, establecerá en el RTC en la fecha y hora cuando se compiló este línea
  }
}
void loop(){
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
  delay(3000);



}
