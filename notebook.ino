#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define input 10
#define alphabetSize 8
#define alphabetLastIndex 7

char detectedButton = '0';
char alphabet[alphabetSize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', ' '};
int letterIndex = alphabetLastIndex;
int positionX = 0;

char detectButton() {
  int analog = analogRead(A0);
  if (analog < 50) detectedButton = 'R';
  else if ( (analog > 95) && (analog < 150) ) detectedButton = 'U';
  else if ( (analog > 240) && (analog < 350) ) detectedButton = 'D';
  else if ( (analog > 400) && (analog < 500) ) detectedButton = 'L';
  else if ( (analog > 600) && (analog < 750) ) detectedButton = 'S';
  else detectedButton = '0';
}

void handleUp() {
  if (letterIndex < alphabetLastIndex) {
    letterIndex++;
  } else {
    letterIndex = 0;
  }
}

void handleDown() {
  if (letterIndex > 0) {
    letterIndex--;
  } else {
    letterIndex = alphabetLastIndex;
  }
}

void handleRight() {
  positionX++;
  letterIndex = alphabetLastIndex;
}

void handleLeft() {
  positionX--;
  letterIndex = alphabetLastIndex;
}

void setup() {
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(input, OUTPUT);
  digitalWrite(input, HIGH);
}

void loop() {
  while(detectedButton == '0') {
    detectButton();  
  }

  if(detectedButton == 'U') {
    handleUp();
  } else if (detectedButton == 'D') {
    handleDown();
  } else if (detectedButton == 'R') {
	handleRight();
  } else if (detectedButton == 'L') {
    handleLeft();
  }
  
  lcd.setCursor(positionX, 0);
  lcd.print(alphabet[letterIndex]);
  delay(200);
  detectedButton = '0';
}
