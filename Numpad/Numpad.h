/*
  Simple library to scan rows and colums of a numpad
*/

#ifndef Numpad_h
#define Numpad_h

#include "Arduino.h"

class Numpad {
  public:
    Numpad(int cols[], int rows[], int colSize, int rowSize);
    void scan();
    int getPressedKeys(int i);
    void resetPrevious();
    int getNumberPressed();
    bool skipPrevious = true;
    //void overrideDefaultKeymap(int[][] keymap);
  private:
    int keymap[6][4] = {
      {0x68, 0x69, 0x6A, 0x6B},
      {0x53, 0x54, 0x55, 0x56},
      {0x5F, 0x60, 0x61, 0x57},
      {0x5C, 0x5D, 0x5E, 0x00},
      {0x59, 0x5A, 0x5B, 0x58},
      {0x62, 0x00, 0x63, 0x00}
    };
    int* _rows;
    int* _cols;
    int _colSize;
    int _rowSize;
    int* _pressed;
    int* _previous;
    int _nrPressed;
    void debugMatrix(int col, int row);
    void setAllToValue(int val);
    void activateOneCol(int col);
    void initCols();
    void initRows();
    void resetPressed();
    void recordPrevious();
    bool wasPressed(int key);
};

#endif
