/*
 *  Created by TheCircuit
*/

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo servo;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  servo.attach(2);//D4
  servo.write(0);
  delay(1000);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "35 3C B1 15") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" Jaa Simran Jaa!");
    servo.write(90);
    delay(10000);
    servo.write(0);
    //Serial.println("Pehli Fursat mein Nikal!");
    //Serial.println();
    statuss = 1;
  }
  else
  {
    Serial.println(" Access Denied ");
    delay(3000);
  }
}

//hello world
