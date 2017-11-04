#include "Arduino.h"
#include "Numpad.h"

#define DIGITAL_OFF 0
#define DIGITAL_ON 1
#define MAX_KEYS 6

Numpad::Numpad(int cols[], int rows[], int colSize, int rowSize) {
  _cols = cols;
  _rows = rows;

  // TODO: dynamic size
  _colSize = colSize;
  _rowSize = rowSize;
  _pressed = new char[MAX_KEYS];
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
}

void Numpad::debugMatrix(int col, int row) {
  Serial.print(col);
  Serial.print(" ");
  Serial.print(row);
  Serial.print("\n");
}

int Numpad::getNumberPressed() {
  return _nrPressed;
}

void Numpad::scan() {
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

char Numpad::getPressedKeys(int i) {
  if (i < _nrPressed) {
      return _pressed[i];
  }
  return '-';
}
