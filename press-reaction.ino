int button1 = 3;
int led1 = 4;
int button2 = 5;
int led2 = 6;
int led0 = 8;

void setup() {
  randomSeed(analogRead(0));
  pinMode(led1, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(led2, OUTPUT);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led0, OUTPUT);
}

void loop() {
  delay(random(2000, 7000));
  digitalWrite(led0, HIGH);
  while (digitalRead(button2) == 1 && digitalRead(button1) == 1 ) {};
  if(digitalRead(button1) == 0){
    digitalWrite(led1, HIGH);
  }
  if(digitalRead(button2) == 0) {
    digitalWrite(led2, HIGH);
  }
  delay(2000);
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}
