#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
}

int wallColumn = 16;
const int wallRow = 2;

void loop() {
  lcd.setCursor(wallColumn, wallRow);
  lcd.print("|");
  delay(300);
  lcd.clear();
  wallColumn--;
  if(wallColumn ==-1) {
    wallColumn = 16;
    delay(random(100, 1000));
  }
}
