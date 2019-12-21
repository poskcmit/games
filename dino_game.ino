#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
}

int suit = 0;

void loop() {
  lcd.setCursor(2, 2);
  lcd.write(byte(suit));
  delay(300);
  suit++;
  if(suit > 1) {
    suit = 0;
  }
}
