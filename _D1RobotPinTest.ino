//  D1Robot's LCD shield pin header test sketch. 
//  D1Robot's one is similar to DFRobot's one, but some pin headers' definition seems to be not the same.
//  
//  (c) 2016 Akio Fujimoto.

// include the libraries.
#include <LiquidCrystal.h>

// LCD 4-bit mode uses some pins.  So wedeclare pins to be skipped
int skipPin[] = {8, 9, 4, 5, 6, 7};
//bool isSkip = false;

LiquidCrystal lcd = LiquidCrystal(8, 9, 4, 5, 6, 7);  // create an instance for LCD module.

void debug(int delayTime) {  // you may delete this block after confirmation was successfully completed.
  int i = 0;
  for (int j = 0; j <= 19; j++) {
    Serial.print(j);
    if (!(j < 10))Serial.print(" ");
    if (j == 19)Serial.println();
  }  // end loop j.
  for (int j = 0; j <= 19; j++) {
    //    Serial.print(j == ignScan(j) ? 1 : 0 ); // 1 is output, 0 is input.
    Serial.print(pinStatus(j));
    if (!(j < 10))Serial.print("  ");
    if (j == 19)Serial.println();
  }  // end loop k.
  delay(delayTime);
  Serial.println();
  Serial.println();
}  // end debug.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i <= 19; i++) {
    if (ignScan(i) != true) { // if the pin is not listed ignore list,
      pinMode(i, OUTPUT);
      pinMode(i, LOW);
    }
  }
  //  pinMode(11, OUTPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print(millis() / 1000);
  debug(1000);
}

bool ignScan(byte pin) {  // this determine whether the specified pin is to be ignored or not.
  bool isSkip = false;
  do {
    //    for(int j=0 ; j<=19 ; j++){
    for (int i = 0; i <= sizeof(skipPin) / sizeof(skipPin[0]); i++) {
      // ERR/ (pin == skipPin[i]) ? isSkip = true;  /* false --> do nothing */
      if (pin == skipPin[i]) {
        isSkip = true;
        break;
      }
    }
  } while (!isSkip);
  return isSkip;
}

// implemented the function to read the status of pin, and return the status.
// It manipulates three AVR's internal registers.  (Arduino's pin name -> AVR register's name(see below))
// D0..7 -> DDRD,   D8..13 -> DDRB,  D14(A0)..D19(A5) -> DDRC.   1 is output, 0 is input.
byte pinStatus(byte pin) {  
  byte result = 0;
  if (0 <= pin && pin <= 7) {
    result = ((unsigned int)DDRD >> pin) & 0b00000001;
  } else if (8 <= pin && pin <= 13) {
    result = ((unsigned int)DDRB >> (pin - 8)) & 0b00000001;
  } else if (14 <= pin && pin <= 19) {
    result = ((unsigned int)DDRC >> (pin - 14)) & 0b00000001;
  }
  return result;  // 0:Input,  1:Output.
}

