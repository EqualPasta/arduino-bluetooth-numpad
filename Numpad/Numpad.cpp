#include "Arduino.h"
#include "Numpad.h"

#define DIGITAL_OFF 0
#define DIGITAL_ON 1
#define MAX_KEYS 6
#define NO_KEY 0x00

Numpad::Numpad(int cols[], int rows[], int colSize, int rowSize) {
  _cols = cols;
  _rows = rows;

  // TODO: dynamic size
  _colSize = colSize;
  _rowSize = rowSize;
  _pressed = new int[MAX_KEYS];
  _previous = new int[MAX_KEYS];
  _nrPressed = 0;
  initRows();
  initCols();
}

void Numpad::initCols() {
  for (int i = 0; i < _colSize; i++) {
    pinMode(_cols[i], OUTPUT);
  }
}

void Numpad::initRows() {
  for (int i = 0; i < _rowSize; i++) {
    pinMode(_rows[i], INPUT_PULLUP);
  }
}

void Numpad::setAllToValue(int val) {
  for (int i = 0; i < _colSize; i++) {
    digitalWrite(_cols[i], val);
  }
}

void Numpad::activateOneCol(int col) {
  setAllToValue(DIGITAL_ON);
  digitalWrite(col, DIGITAL_OFF);
}

void Numpad::resetPressed() {
    _nrPressed = 0;
    for (int i = 0; i< MAX_KEYS; i++) {
      _pressed[i] = NO_KEY;
    }
}

void Numpad::debugMatrix(int col, int row) {
  Serial.print(col);
  Serial.print(" ");
  Serial.print(row);
  Serial.print("\n");
}

bool Numpad::wasPressed(int key) {
  for (int i = 0; i<MAX_KEYS; i++) {
    if (key == _previous[i]) {
      return true;
    }
  }
  return false;
}

void Numpad::recordPrevious() {
  for (int i = 0; i< MAX_KEYS; i++) {
    _previous[i] = _pressed[i];
  }
}

void Numpad::resetPrevious() {
  for (int i = 0; i< MAX_KEYS; i++) {
    _previous[i] = NO_KEY;
  }
}

int Numpad::getNumberPressed() {
  return _nrPressed;
}

void Numpad::scan() {
  recordPrevious();
  resetPressed();

  int i = 0;
  for (int col = 0; col < _colSize; col++) {
    activateOneCol(_cols[col]);
    for (int row = 0; row < _rowSize; row++) {
      int val = digitalRead(_rows[row]);
      if (val == 0 && i < MAX_KEYS) {
        //debugMatrix(col, row);
        _pressed[i] = keymap[col][_rowSize - row -1];
        i = i + 1;
        _nrPressed = i;
      }
    }
  }
}

int Numpad::getPressedKeys(int i) {
  if (i < _nrPressed) {
      if (skipPrevious && wasPressed(_pressed[i])) {
        return NO_KEY;
      }
      return _pressed[i];
  }
  return NO_KEY;
}
