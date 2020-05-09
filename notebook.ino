#include <EEPROM.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#define input 10
#define alphabetSize 8
#define alphabetLastIndex 7

char detectedButton = '0';
char alphabet[alphabetSize] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', ' '};
int letterIndex = 0;
int position = 0;

int state[32] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};

void printState() {
  for (int i = 0; i < 32; ++i) {
    lcd.setCursor( i % 16, i / 16 );
    int letterIndex = state[i];
    lcd.print(alphabet[letterIndex]);
  }
}

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
  state[position] = letterIndex;
  printState();
}

void handleDown() {
  if (letterIndex > 0) {
    letterIndex--;
  } else {
    letterIndex = alphabetLastIndex;
  }
  state[position] = letterIndex;
  printState();
}

void handleRight() {
  // EEPROM.put(0, letterIndex);
  if (position < 31) {
  	position++;
  } else {
    position = 0;
  }
  letterIndex = 0;
}

void handleLeft() {
  // EEPROM.put(0, letterIndex);
  if (position > 0) {
  	position--;
  } else {
    position = 31;
  }
  letterIndex = 0;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(A0, INPUT);
  pinMode(input, OUTPUT);
  digitalWrite(input, HIGH);
  printState();
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
  
  //lcd.setCursor(position % 16, position / 16);
 
  //lcd.print(alphabet[letterIndex]);
  delay(200);
  detectedButton = '0';
  // char s = alphabet[EEPROM.read(0)];
  // Serial.println(s);
}
