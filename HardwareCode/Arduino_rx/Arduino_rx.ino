#include <SoftwareSerial.h>
//SoftwareSerial ArduinoUno(6,7); // (tx,rx)
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(500);
}
char c;
void loop() 
{
  lcd.setCursor(0, 1);  
  lcd.clear();
  lcd.print(Serial.read());
  //Serial.println(ArduinoUno.read());
  delay(1000);
}
