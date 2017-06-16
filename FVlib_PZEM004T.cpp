#include "FVlib_PZEM004T.h"

#define timeout 1000

FVlib_PZEM004T::FVlib_PZEM004T(SoftwareSerial &_port) {
  softPort = &_port;

}

float FVlib_PZEM004T::readVoltage() {
  //Set adress:
  setCommunicationAddress();

  /*
  //Read voltage:
  (*softPort).write(0xB0);
  (*softPort).write(0xC0);
  (*softPort).write(0xA8);
  (*softPort).write(0x01);
  (*softPort).write(0x01);
  (*softPort).write((byte) 0x00);
  (*softPort).write(0x1E);
  delay(500);
  Serial.print("voltage:");
  receive(true); */

  Serial.print("voltage:");
  (*softPort).write(askVoltage, 7);
  //delay(500);
  receive(true);


}

/*boolean FVlib_PZEM004T::send(byte* message) {
  (*softPort).write(*message, 7);
}*/


boolean FVlib_PZEM004T::receive(boolean printBuffer) {
  if (printBuffer == true) Serial.println("receiving...");
    for(byte index = 0; index < 7; index++) {
      waitBufferToFill();
      buffer[index] = (*softPort).read();
      if (printBuffer == true) Serial.println(buffer[index], HEX);
    }
    if((*softPort).available() > 0) return true;
    else return false;
}

boolean FVlib_PZEM004T::waitBufferToFill() {
// Return: false Ok, true Error
  unsigned long timeIn = millis();
  while((*softPort).available() < 1) {
    if ((millis() - timeIn) > timeout) return true; // Timeout Error
  }
  return false;
}

void FVlib_PZEM004T::setCommunicationAddress() {
  Serial.println("Setting comunication address");
  (*softPort).write(setAddress, 7);
  //delay(500);
  receive(true);
}
