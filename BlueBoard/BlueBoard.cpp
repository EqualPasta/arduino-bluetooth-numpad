#include "Arduino.h"
#include "BlueBoard.h"
#include "BluefruitConfig.h"
#include "Adafruit_BluefruitLE_SPI.h"

BlueBoard::BlueBoard() {
  ble = new Adafruit_BluefruitLE_SPI(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
}

void BlueBoard::sendKeys(int keys[], int nrOfPressed) {
  ble->print("AT+BLEKEYBOARDCODE=");
  ble->print("00-00");
  for (int i = 0; i < nrOfPressed; i++) {
    ble->print("-");
    ble->print(String(keys[i], HEX));
  }
  ble->println("");
  ble->waitForOK();
}

void BlueBoard::resetKeys() {
  ble->println("AT+BLEKEYBOARDCODE=00-00");
  ble->waitForOK();
}

void BlueBoard::setup() {
  if ( !ble->begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  ble->echo(false);
  ble->info();

  // Set name of device
  if (! ble->sendCommandCheckOK(F( "AT+GAPDEVNAME=Numpad" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  if ( ble->isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble->sendCommandCheckOK(F( "AT+BLEHIDEn=1" ))) {
      error(F("Could not enable Keyboard"));
    }
  } else
  {
    if (! ble->sendCommandCheckOK(F( "AT+BLEKEYBOARDEN=1"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  if (! ble->reset() ) {
    error(F("Couldn't reset??"));
  }
}

void BlueBoard::error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
