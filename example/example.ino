#include "FVlib_PZEM004T.h"

FVlib_PZEM004T modul(2, 3);

void setup() {
 Serial.begin(9600);

 modul.readVoltage();

}

void loop() {
  // put your main code here, to run repeatedly:

}
