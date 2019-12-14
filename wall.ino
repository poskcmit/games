#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
}

int wallColumn = 0;
const int wallRow = 2;

void loop() {
  lcd.setCursor(wallColumn, wallRow);
  lcd.print("|");
  delay(200);
  wallColumn--;
  if(wallColumn == 0) {
    wallColumn = 16;
  }
  delay(random(100, 1000));
}
