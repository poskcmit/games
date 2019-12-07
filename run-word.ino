#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char detectButton(int portValue) {
  if(portValue <= 80) return 'R';
  if(portValue > 80 && portValue <= 200) return 'U';
  if(portValue > 200 && portValue <= 400) return 'D';
  if(portValue > 400 && portValue <= 600) return 'L';
  if(portValue > 600 && portValue <= 800) return 'S';
  return 'N';
}

void setup() {
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
}

int row = 0;
int column = 0;

void loop() {
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') column++;
    if(button == 'L') column--;
  }
  lcd.setCursor(column, row);
  lcd.print("A");
  delay(250);
  lcd.clear();
}
