#include <Arduino.h>
#include <Numpad.h>
#include <SPI.h>
#include "HID-Project.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "BluefruitConfig.h"

#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

int rows[] = {22, 19, 21, 20};
int cols[] = {13, 12, 11, 9, 10, 6};
Numpad numpad(cols, rows, 6, 4);

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  setupBle();
}

void loop() {
  //TODO: read another button to establish if bluetooth or not
  numpad.scan();
  int pressed = numpad.getNumberPressed();
  if (pressed > 0) {
    prepareKeysAndSend(pressed);
  }
  delay(70);
}

void prepareKeysAndSend(int nrOfPressed) {
  int keys[nrOfPressed];
  for (int i = 0; i < nrOfPressed; i++) {
    keys[i] = numpad.getPressedKeys(i);
  }

  sendKeys(keys, nrOfPressed);
}

void sendKeys(int keys[], int nrOfPressed) {
  if (Serial) {
    sendKeysUSB(keys, nrOfPressed);
  }
  else {
    sendKeysBLE(keys, nrOfPressed);
    resetKeysBLE();
  }
}

void sendKeysUSB(int keys[], int nrOfPressed) {
  for (int i = 0; i < nrOfPressed; i++) {
    Keyboard.write(KeyboardKeycode(keys[i]));
  }
}

void sendKeysBLE(int keys[], int nrOfPressed) {
  ble.print("AT+BLEKEYBOARDCODE=");
  ble.print("00-00");
  for (int i = 0; i < nrOfPressed; i++) {
    ble.print("-");
    ble.print(String(keys[i], HEX));
  }
  ble.println("");
  ble.waitForOK();
}

void resetKeysBLE() {
  ble.println("AT+BLEKEYBOARDCODE=00-00");
  ble.waitForOK();
}

void setupBle() {
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  ble.echo(false);
  ble.info();

  // Set name of device
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Numpad" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BLEHIDEn=1" ))) {
      error(F("Could not enable Keyboard"));
    }
  } else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BLEKEYBOARDEN=1"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }
}

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
