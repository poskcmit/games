#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define RetroEclairage 10

char detectButton(int analog) {
  if (analog < 50) return 'R';
  if ( (analog > 95) && (analog < 150) ) return 'U';
  if ( (analog > 240) && (analog < 350) ) return 'D';
  if ( (analog > 400) && (analog < 500) ) return 'L';
  if ( (analog > 600) && (analog < 750) ) return 'S';
}

void setup() {
  randomSeed(A0);
  lcd.begin(16, 2);
  pinMode(RetroEclairage, OUTPUT);
  digitalWrite(RetroEclairage, HIGH);
  delay(100);
  digitalWrite(RetroEclairage, LOW);
}

int time = 0;
// дз завести переменную - счетчик яблок
int x = 0;
int y = 0;

int appleX = 0;
int appleY = 0;
boolean appleFlag = true;

void loop() {
  // перемещения персонажа
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') {
      if(x < 12) {
      	x++;
      }
    }
    if(button == 'L') {
      if(x > 0) {
      	x--;
      }
    }
    if(button == 'U') {
      if(y > 0) {
      	y--;
      }
    }
    if(button == 'D') {
      if (y < 1) {
      	y++;
      }
    }
  }
  
  // логика посторонних объектов
  if (appleFlag) {
    appleX = random(0, 13);
    appleY = random(0, 2);
    appleFlag = false;
  }
  
  if (appleX == x && appleY == y) {
    appleFlag = true;
    // дз здесь мы съели яблоко, нужно увеличить счетчик яблок на 1
  }
  
  time += 100;
  
  // отрисовка
  lcd.setCursor(appleX, appleY);
  lcd.print("o");
  lcd.setCursor(x, y);
  lcd.print("A");
  lcd.setCursor(13, 0);
  lcd.print("|");
  lcd.setCursor(13, 1);
  lcd.print("|");
  lcd.setCursor(14, 1);
  lcd.print(time / 1000);
  // дз здесь нужно отрисовать счетчик на (14, 0)
  delay(100);
  lcd.clear();
}
