#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define input 10

char detectButton(int analog) {
  if (analog < 50) return 'R';
  if ( (analog > 95) && (analog < 150) ) return 'U';
  if ( (analog > 240) && (analog < 350) ) return 'D';
  if ( (analog > 400) && (analog < 500) ) return 'L';
  if ( (analog > 600) && (analog < 750) ) return 'S';
  return '0';
}

String letters[6] = {"a", "b", "c", "d", "e", " "};


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(input, OUTPUT);
  digitalWrite(input, HIGH);
}

int letterIndex = 0;
char pressedButton = '0';

void loop() {
  int buttonValue = analogRead(A0);
  Serial.println(buttonValue);
  while(buttonValue > 900) {Serial.println(buttonValue);};
  pressedButton = detectButton(buttonValue);
  Serial.println(pressedButton);
  lcd.setCursor(0, 0);
  lcd.print(letters[0]);
}

