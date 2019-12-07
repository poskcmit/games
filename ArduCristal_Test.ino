//=== include the library code: =======================================
#include <LiquidCrystal.h>
//--- Define keys numbers ---------------------------------------------
#define keyNONE    0
#define keyRIGHT   1
#define keyUP      2
#define keyDOWN    3
#define keyLEFT    4
#define keySELECT  5
//--- Symbols ----------------------------------------------------------
#define Right 	0x7E					// Right arrow 0x7E
#define Left	0x7F					// Left arrow 0x7F
//----------------------------------------------------------------------
#define DELTA     10					// Contrast step
#define Debounce 200
//=== Make some custom characters: =====================================
static byte ArrUp[8]    = {				// Up arrow
	0b00000,0b00100,0b01110,0b10101,0b00100,0b00100,0b00000,0b00000}; 
static byte ArrDown[8]  = {				// Down arrow
    0b00000,0b00000,0b00100,0b00100,0b10101,0b01110,0b00100,0b00000};
static byte Heart[8]    = {				// Heart
	0b00000,0b01010,0b11111,0b11111,0b11111,0b01110,0b00100,0b00000};  
static byte Smiley[8]   = {				// Smiley
	0b00000,0b00000,0b01010,0b00000,0b00000,0b10001,0b01110,0b00000};  
static byte Frownie[8]  = {				// Frownie
	0b00000,0b00000,0b01010,0b00000,0b00000,0b00000,0b01110,0b10001};  
static byte ArmUp[8]   = {				// Up arm
	0b00100,0b01010,0b00100,0b10101,0b01110,0b00100,0b00100,0b01010};  
static byte ArmDown[8] = {				// Down arm
	0b00100,0b01010,0b00100,0b00100,0b01110,0b10101,0b00100,0b01010};
//----------------------------------------------------------------------
int Key, Key_Press, Key_S, Key_L, Key_D, Key_U, Key_R;
unsigned char BackL = 200;				// Initial backlight
//--- Initialize the library with the numbers of the interface pins ----
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);	// (rs, enable, d4, d5, d6, d7)
//######################################################################
void Culc_Press (int Key_min, int Key_max) {
	Key = 0; Key_Press = 0;
	for (int i = 5; i >= 1; i--) {
		do {Key_Press = analogRead(0); delay (Debounce);}
		while(Key_Press < Key_min || Key_Press > Key_max);
		Key = Key + Key_Press/5;
		if ((i-1) > 0) {
			lcd.setCursor(12, 0);
			lcd.print(i - 1); lcd.print(" tm");
			lcd.setCursor(10, 1); lcd.print (Key_Press);		
			delay (Debounce);
		}
		else delay (Debounce);
	}	
}
//=== Define key "Select" value ========================================
void Define_Select () {	
	lcd.clear(); lcd.print("Press S-key 5 tm");
	lcd.setCursor(0, 1); lcd.print("S-value = ");
	Culc_Press(600, 800); Key_S = Key;
	lcd.clear(); lcd.print("Key Select value");
	lcd.setCursor(0, 1); lcd.print("= "); lcd.print(Key_S);
}
//=== Define key "Left" value ==========================================
void Define_Left () {
	lcd.clear(); lcd.print("Press L-key 5 tm");
	lcd.setCursor(0, 1); lcd.print("L-value = ");
	Culc_Press(400, 600); Key_L = Key;
	lcd.clear(); lcd.print("Key Left value  ");
	lcd.setCursor(0, 1); lcd.print("= "); lcd.print(Key_L);
}
//=== Define key "Down" value ==========================================
void Define_Down () {
	lcd.clear(); lcd.print("Press D-key 5 tm");
	lcd.setCursor(0, 1); lcd.print("D-value = ");
	Culc_Press(200, 300); Key_D = Key;
	lcd.clear(); lcd.print("Key Down value  ");
	lcd.setCursor(0, 1); lcd.print("= "); lcd.print(Key_D);
}
//=== Define key "Up" value ============================================
void Define_Up () {
	lcd.clear(); lcd.print("Press U-key 5 tm");
	lcd.setCursor(0, 1); lcd.print("U-value = ");
	Culc_Press(50, 150); Key_U = Key;
	lcd.clear(); lcd.print("Key Up value    ");
	lcd.setCursor(0, 1); lcd.print("= "); lcd.print(Key_U);
}
//=== Read keypress ====================================================
int Read_Key() {
	Key_Press = analogRead(0);	// read the value from the sensor
	if (Key_Press > 1000)         return keyNONE;
	if (Key_Press < (Key_R + 10)) return keyRIGHT;	// 0 
	if (Key_Press < (Key_U + 10)) return keyUP;		// 97 
	if (Key_Press < (Key_D + 10)) return keyDOWN;	// 257
	if (Key_Press < (Key_L + 10)) return keyLEFT;	// 410 
	if (Key_Press < (Key_S + 10)) return keySELECT;	// 640   
	return keyNONE;		// when all others fail, return this...
}
//=== Define backlight brightness value ================================
void DefBright (){
	lcd.clear();        lcd.print("Define value of ");
	lcd.setCursor(0,1); lcd.print("backlight bright");
	delay(2000);
//----------------------------------------------------------------------
	lcd.clear();        lcd.print("Backlight value ");
	lcd.setCursor(0, 1); lcd.print("= "); 
//--- adjust the backlight ---------------------------------------------
	do {
		Key = Read_Key();
		if (Key == keyUP) {
			if ((0xFF - DELTA) >= BackL) BackL +=DELTA;
			else BackL = 0xFF;
		}
		else if (Key == keyDOWN) {
			if (DELTA <= BackL) BackL -=DELTA;
			else BackL = 0;
		}
		lcd.setCursor(2,1); lcd.print("   "); 		// Clear old value
		lcd.setCursor(2,1); lcd.print(BackL);
		analogWrite(10, BackL);						// set new backlight
		delay(Debounce);
	}
	while (Key != keySELECT);	
} 
//=== Custom chars test-show ===========================================
void CustChars () {
	lcd.clear();        lcd.print("Custom graphics ");
	lcd.setCursor(0,1); lcd.print(" chars examples ");
	delay(2000); lcd.clear();
//----------------------------------------------------------------------  
	lcd.print("I ");  	     lcd.write(byte(2));   	// Heart
	lcd.print(" Arduino! "); lcd.write(byte(3));	// Smiley
	lcd.setCursor(10, 1);	 lcd.write(byte(4));	// Frownie
	while (Key != keySELECT) {
		lcd.setCursor(4, 1); lcd.write(byte(5));	// Arm up 
		delay(250);  
		lcd.setCursor(4, 1); lcd.write(byte(6));    // Arm down 
		delay(250); 
		Key = Read_Key();
	}	
}
//=== Show LCD chars table =============================================
void ASCIIchar () {
	lcd.clear();        lcd.print("ASCII characters");
	lcd.setCursor(0,1); lcd.print(" from LCD table ");
	delay(2000); lcd.clear();
	lcd.setCursor(0, 0); lcd.print("DECIMAL = ");
	lcd.setCursor(0, 1); lcd.print("ASCII   = ");
	int count = 33;
	char ascii = 0x00 + 33;
	while(count != 235) {
		lcd.setCursor(10, 0); lcd.print("    ");
		lcd.setCursor(10, 0); lcd.print(count);
		lcd.setCursor(10, 1); lcd.print("    ");
		lcd.setCursor(10, 1); lcd.print(ascii);
		count++; ascii++;
		delay(1000);		
		Key = Read_Key();
		if (Key == keySELECT) return;
	}
}
//=== Show keys analog value ===========================================
void KeysValue (){
	lcd.clear();        lcd.print("Show keypad keys");
	lcd.setCursor(0,1); lcd.print(" analog values  ");
	delay(2000); lcd.clear();
	lcd.print("S:"); lcd.print(Key_S); lcd.print(" ");
	lcd.print("L:"); lcd.print(Key_L); lcd.print(" ");
	lcd.print("R:"); lcd.print(Key_R);
	lcd.setCursor(0,1); 
	lcd.print("U:"); lcd.print(Key_U); lcd.print(" ");
	lcd.print("D:"); lcd.print(Key_D);
	delay (4000);
}		
//######################################################################
void setup() {
	Serial.begin(9600);
//--- Set up the LCD's number of columns and rows: ---------------------
	lcd.begin(16, 2);		// start the library: (cols, rows)
//--- Set initial backlight brightness ---------------------------------
	pinMode(10, OUTPUT); analogWrite(10, BackL);
//--- Sends the custom symbols to LCD ----------------------------------
	lcd.createChar(0, ArrUp);
	lcd.createChar(1, ArrDown);
	lcd.createChar(2, Heart);
	lcd.createChar(3, Smiley);
	lcd.createChar(4, Frownie);
	lcd.createChar(5, ArmUp);
	lcd.createChar(6, ArmDown);
//--- Print prompt to LCD ----------------------------------------------
//..................................0123456789012345....................
	lcd.setCursor(0, 0); lcd.print("ArduCrital Test!");
	lcd.setCursor(0, 1); lcd.print("by V.S.Ignatenko"); delay(4000);
	lcd.setCursor(0, 0); lcd.print("16x02 LCD Keypad");
	lcd.setCursor(0, 1); lcd.print("Define all keys!"); delay(4000);
	Define_Select (); delay(2000); Define_Left (); delay(2000);
	Define_Down ();   delay(2000); Define_Up ();   delay(2000);
	lcd.clear(); lcd.print("Key Right value ");
	lcd.setCursor(0, 1); lcd.print("= "); lcd.print(Key_R);
	delay(2000);
}
//######################################################################
void loop() {
//--- Print menu prompt ------------------------------------------------
	lcd.clear(); 
	lcd.write (Left);   lcd.print (":Bright ");
	lcd.write (Right);  lcd.print (":Char ");
	lcd.setCursor(0,1);
	lcd.write(byte(0)); lcd.print (":SymbTab ");
	lcd.write(byte(1)); lcd.print (":Keys");
//--- read the key continuously until any of keys is pressed -----------
	Key = Read_Key();
//--- Depending on which key was pushed, perform an action -------------
	switch (Key) {				
		case keyLEFT:  DefBright (); break; // Define brightness value  
		case keyRIGHT: CustChars (); break; // Custom chars test-show
		case keyUP:    ASCIIchar (); break; // Show LCD chars table
		case keyDOWN:  KeysValue (); break;	// Show keys analog value
		case keySELECT:  break;
	}
	delay (Debounce);
}
