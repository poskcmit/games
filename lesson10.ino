#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

char detectButton(int portValue) {
  if(portValue <= 80) return 'R';
  else if(portValue <= 200) return 'U';
  else if(portValue <= 400) return 'D';
  else if(portValue <= 600) return 'L';
  else if(portValue <= 800) return 'S';
  return 'N';
}

void setup() {
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
}
int x = 0;
int y = 0;
void loop() {
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') {
      // x = x + 1;
      x++;
    }
  }
  
  lcd.setCursor(x, y);
  lcd.print("A");
  lcd.delay(100);
  lcd.clear();
}
