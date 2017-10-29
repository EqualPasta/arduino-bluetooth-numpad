#define ROW_0 22
#define ROW_1 19
#define ROW_2 21
#define ROW_3 20

#define COL_0 13
#define COL_1 12
#define COL_2 11
#define COL_3 10
#define COL_4 9
#define COL_5 6

#define DIGITAL_OFF 0
#define DIGITAL_ON 1

int rows[] = {ROW_0, ROW_1, ROW_2, ROW_3};
int cols[] = {COL_0, COL_1, COL_2, COL_3, COL_4, COL_5};
int current = 0;

void setup() {
  pinMode(ROW_0, INPUT_PULLUP);
  pinMode(ROW_1, INPUT_PULLUP);
  pinMode(ROW_2, INPUT_PULLUP);
  pinMode(ROW_3, INPUT_PULLUP);
  pinMode(COL_0, OUTPUT);
  pinMode(COL_1, OUTPUT);
  pinMode(COL_2, OUTPUT);
  pinMode(COL_3, OUTPUT);
  pinMode(COL_4, OUTPUT);
  pinMode(COL_5, OUTPUT);
  Serial.begin(9600);
}

void setAllToValue(int val) {
  digitalWrite(COL_0, val);
  digitalWrite(COL_1, val);
  digitalWrite(COL_2, val);
  digitalWrite(COL_3, val);
  digitalWrite(COL_4, val);
  digitalWrite(COL_5, vpual);
}

void activateOneRow(int row) {
  setAllToValue(DIGITAL_ON);
  digitalWrite(row, DIGITAL_OFF);
}

void loop() {
  current = (current + 1) % 6;
  activateOneRow(cols[current]);
  for (int i = 0; i < 4; i++) {
    int val = digitalRead(rows[i]);
    if (val == 0) {
      Serial.print(current);
      Serial.print(" ");
      Serial.print(i);
      Serial.print("\n");
    }
  }
  delay(50);
}
