#include <LiquidCrystal.h>
const int RS = 6,EN = 7, d4 = 11, d5 = 8, d6 = 9, d7 = 10;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);
void setup() 
{
  // put your setup code here, to run once:
   lcd.begin(16, 2);
                      // Print a message to the LCD.
  lcd.print("hello, world!");

}

void loop() 
{
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

}
