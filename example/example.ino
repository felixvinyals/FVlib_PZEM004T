#include "FVlib_PZEM004T.h"

SoftwareSerial port(2, 3);
FVlib_PZEM004T modul(port);

void setup() {
 Serial.begin(9600);
 port.begin(9600);


}

void loop() {
  float v, i, p;
  
  Serial.print("V: ");
  v = modul.readVoltage();
  Serial.println(v);
  delay(500);
  
  Serial.print("I: ");
  i = modul.readCurrent();
  Serial.println(i);
  delay(500);
  
  Serial.print("P: ");
  p = modul.readPower();
  Serial.println(p);
  delay(500);

  Serial.println(String("calculated power: ") + String(v * i));
}