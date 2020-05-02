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

void loop() {
  int buttonValue = analogRead(A0);
  if(buttonValue < 900) {
    char button = detectButton(buttonValue);
    if(button == 'R') {
    }
    if(button == 'L') {
    }
    if(button == 'U') {
    }
    if(button == 'D') {
    }
  }
}
