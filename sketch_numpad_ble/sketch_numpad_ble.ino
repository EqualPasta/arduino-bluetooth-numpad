#include <Arduino.h>
#include <Numpad.h>
#include <BlueBoard.h>
#include <SPI.h>
#include "HID-Project.h"

#define CONNECTIVITY_MODE    23
#define BLUETOOTH_MODE    1
#define USB_MODE    0

int rows[] = {22, 19, 21, 20};
int cols[] = {13, 12, 11, 9, 10, 6};
Numpad numpad(cols, rows, 6, 4);
BlueBoard blueBoard;

void setup() {
  Serial.begin(9600);
  pinMode(CONNECTIVITY_MODE, INPUT_PULLUP);

  Keyboard.begin();
  blueBoard.setup();
}

void loop() {
  numpad.scan();

  int pressed = numpad.getNumberPressed();
  if (pressed > 0) {

    int mode = digitalRead(CONNECTIVITY_MODE);
    if (mode == BLUETOOTH_MODE) {
      sendKeysBLE(pressed);
      blueBoard.resetKeys();
    }
    else {
      sendKeysUSB(pressed);
    }
  }
  delay(70);
}

void sendKeysUSB(int nrOfPressed) {
  for (int i = 0; i < nrOfPressed; i++) {
    Keyboard.write(KeyboardKeycode(numpad.getPressedKeys(i)));
  }
}

void sendKeysBLE(int nrOfPressed) {
  int keys[nrOfPressed];
  for (int i = 0; i < nrOfPressed; i++) {
    keys[i] = numpad.getPressedKeys(i);
  }

  blueBoard.sendKeys(keys, nrOfPressed);
}
