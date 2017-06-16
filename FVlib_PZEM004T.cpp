#include "FVlib_PZEM004T.h"

#define timeout 1000

FVlib_PZEM004T::FVlib_PZEM004T(SoftwareSerial &_port) {
  softPort = &_port;

}

float FVlib_PZEM004T::readVoltage() {
  float voltage = 0;

  //Set adress:
  setCommunicationAddress();

  (*softPort).write(askVoltage, 7);
  receive(false);

  voltage = (float) buffer[3] / 10;
  voltage = voltage + buffer[2];
  return(voltage);
}

float FVlib_PZEM004T::readCurrent() {
  float current = 0;

  setCommunicationAddress();

  (*softPort).write(askCurrent, 7);
  receive(false);

  if (buffer[3] < 10) current = (float) buffer[3] / 10;
  else current = (float) buffer[3] / 100;
  current = current + buffer[2];
  return(current);

}

unsigned int FVlib_PZEM004T::readPower() {
  unsigned int power = 0;

  setCommunicationAddress();

  (*softPort).write(askPower, 7);
  receive(false);

  //Serial.println(buffer[1]);
  //Serial.println(buffer[2]);

  power = buffer[1];
  power = power << 8;
  power = power + buffer[2];
  return(power);

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
    else {
      if (checksumError() == 0) return false;
      else {
        return true;
      }
    }

}

boolean FVlib_PZEM004T::waitBufferToFill() {
// Return: false Ok, true Error
  unsigned long timeIn = millis();
  while((*softPort).available() < 1) {
    if ((millis() - timeIn) > timeout) return true; // Timeout Error
  }
  return false;
}

boolean FVlib_PZEM004T::checksumError() {
// Return: false Ok, true Error
  byte checksum_Sum = 0;

  for (byte index = 0; index < 6; index++) {
    checksum_Sum = checksum_Sum + buffer[index];
  }
  if (checksum_Sum == buffer[6]) return false;
  else {
    Serial.print("CHKSUM Error: ");
    Serial.print("Calculated: ");
    Serial.println(checksum_Sum);
    return true;
  }
}

void FVlib_PZEM004T::setCommunicationAddress() {
  //Serial.println("Setting comunication address");
  (*softPort).write(setAddress, 7);
  receive(false);
}
