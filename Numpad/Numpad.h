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
    char getPressedKeys(int i);
    int getNumberPressed();
    //void overrideDefaultKeymap(char[][] keymap);
  private:
    char keymap[6][4] = {
      {'\377', 'b', 'c', 'd'},
      {'n', '/', '*', '-'},
      {'7', '8', '9', '+'},
      {'4', '5', '6', '?'},
      {'1', '2', '3', 'e'},
      {'0', '?', '.', '?'}
    };
    int* _rows;
    int* _cols;
    int _colSize;
    int _rowSize;
    char* _pressed;
    int _nrPressed;
    void debugMatrix(int col, int row);
    void setAllToValue(int val);
    void activateOneCol(int col);
    void initCols();
    void initRows();
    void resetPressed();
};

#endif
