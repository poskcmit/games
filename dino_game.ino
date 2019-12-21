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

byte suit_1[8] = {
  B01110,
  B10001,
  B01110,
  B00100,
  B00111,
  B00100,
  B01010,
  B10001,
};

byte suit_2[8] = {
  B01110,
  B10001,
  B01110,
  B00100,
  B00111,
  B00100,
  B00100,
  B01010,
};

void setup() {
  lcd.createChar(0, suit_1);
  lcd.createChar(1, suit_2);
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
}

int suit = 0;
int jeffRow = 0;
int jeffColumn = 0;

void loop() {
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') {
      if(jeffColumn < 16) jeffColumn++;
    }
    if(button == 'L') {
      if(jeffColumn > 0) jeffColumn--;
    }
    if(button == 'U') {
      if(jeffRow == 1) jeffRow--;
    }
    if(button == 'D') {
      if(jeffRow == 0) jeffRow++;
    }
  }
  suit++;
  if(suit > 1) {
    suit = 0;
  }
  
  lcd.setCursor(jeffColumn, jeffRow);
  lcd.write(byte(suit));
  delay(250);
  lcd.clear();
}
