#ifndef FVlib_PZEM004T_h
  #define FVlib_PZEM004T_h

  #include <Arduino.h>
  #include <SoftwareSerial.h>

  class FVlib_PZEM004T {
    public:
      // Routines:
      FVlib_PZEM004T::FVlib_PZEM004T(SoftwareSerial &_port);
      float FVlib_PZEM004T::readVoltage();
      float FVlib_PZEM004T::readCurrent();
      unsigned int FVlib_PZEM004T::readPower();


    private:
      // Routines:
      void FVlib_PZEM004T::setCommunicationAddress();
      boolean FVlib_PZEM004T::receive(boolean printBuffer);
      boolean FVlib_PZEM004T::waitBufferToFill();
      boolean FVlib_PZEM004T::checksumError();
      //boolean FVlib_PZEM004T::send(byte* message);
      // Variables:
      SoftwareSerial *softPort;
      byte buffer[7];
      byte askVoltage[7] = {0xB0, 0xC0, 0xA8, 0x01, 0x01, (byte) 0x00, 0x1E};
      byte askCurrent[7] = {0xB1, 0xC0, 0xA8, 0x01, 0x01, (byte) 0x00, 0x1B};
      byte askPower[7] = {0xB2, 0xC0, 0xA8, 0x01, 0x01, (byte) 0x00, 0x1C};
      byte setAddress[7] = {0xB4, 0xC0, 0xA8, 0x01, 0x01, (byte) 0x00, 0x1E};
  };


#endif
