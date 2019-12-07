#include <LiquidCrystal.h>
LiquidCrysal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
}

int row;
int column;

void loop() {
  lcd.setCursor(column, row);
  lcd.print("A");
}
