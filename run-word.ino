#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
}

int row = 0;
int column = 0;
int buttonValue = 0;

void loop() {
  buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    column++;
  }
  lcd.setCursor(column, row);
  lcd.print("A");
  delay(250);
  lcd.clear();
}
