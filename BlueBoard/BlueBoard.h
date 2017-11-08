/*
Library wrapper for bluetooth
*/

#ifndef BlueBoard_h
#define BlueBoard_h

#include "Arduino.h"
#include "Adafruit_BluefruitLE_SPI.h"

class BlueBoard {
  public:
    BlueBoard();
    void setup();
    void sendKeys(int keys[], int nrOfPresse);
    void resetKeys();
  private:
    Adafruit_BluefruitLE_SPI* ble;
    void error(const __FlashStringHelper*err);
};

#endif
