#include <Numpad.h>

int rows[] = {22, 19, 21, 20};
int cols[] = {13, 12, 11, 9, 10, 6};
Numpad numpad(cols, rows, 6, 4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  numpad.scan();
  int pressed = numpad.getNumberPressed();
  for(int i = 0; i<pressed; i++) {
    char pressed = numpad.getPressedKeys(i);
    Serial.println(pressed);
  }

  delay(100);
}
