#include <Wire.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const char* ssid = "EC5";
const char* pass = "123456789";
void setup(){
  Wire.begin(2,0);
  lcd.begin();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("CONNECTED");
 
  Firebase.begin("intellitollgate.firebaseio.com","YiACACoSmOgUEnkYY3s8FNijEoAtkkvabOTX2C51");
}
String value;
void loop(){
  // Nothing Absolutely Nothing!
  Serial.println("done");
  value=Firebase.getString("CARD_NUMBER/pjtKHpOjkYREQZLiZD7TiDJgokb2");
  Serial.println(value);
  lcd.print(value);
}
