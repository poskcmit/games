#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define input 10

char detectButton(int analog) {
  if (analog < 50) return 'R';
  if ( (analog > 95) && (analog < 150) ) return 'U';
  if ( (analog > 240) && (analog < 350) ) return 'D';
  if ( (analog > 400) && (analog < 500) ) return 'L';
  if ( (analog > 600) && (analog < 750) ) return 'S';
}

int letters[6] = {"a", "b", "c", "d", "e", " "};

void setup() {
  lcd.begin(16, 2);
  pinMode(input, OUTPUT);
  digitalWrite(input, HIGH);
  delay(100);
  digitalWrite(input, LOW);
}

int letterIndex = 0;

void loop() {
  int buttonValue = analogRead(A0);
  while(detectButton(buttonValue) != 'U') {};
  letterIndex++;
  lcd.setCursor(0, 0);
  lcd.print(letter[letterIndex]);
}
