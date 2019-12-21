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
int yJeff = 0;
int xJeff = 0;
int xWall = -99;
int yWall = -99;
int hp = 3;

void loop() {
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') {
      if(xJeff < 13) xJeff++;
    }
    if(button == 'L') {
      if(xJeff > 0) xJeff--;
    }
    if(button == 'U') {
      if(yJeff == 1) yJeff--;
    }
    if(button == 'D') {
      if(yJeff == 0) yJeff++;
    }
  }
  suit++;
  if(suit > 1) {
    suit = 0;
  }
  
  if(yWall == -99) {
    xWall = 14;
    yWall = random(0, 2);
  }
  xWall--;
  if(xWall == -1) {
    yWall = -99;
    xWall = -99;
  }
  
  if(xWall == xJeff && yWall == yJeff) {
    hp--;
  }
  
  if(xWall != -99) {
    lcd.setCursor(xWall, yWall);
    lcd.print("|");
  }
  lcd.setCursor(xJeff, yJeff);
  lcd.write(byte(suit));
  lcd.setCursor(14, 0);
  lcd.print("|");
  lcd.setCursor(14, 1);
  lcd.print("|");
  lcd.setCursor(15, 0);
  lcd.print(hp, DEC);
  delay(250);
  lcd.clear();
}
