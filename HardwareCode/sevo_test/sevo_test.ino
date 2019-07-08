#include <Servo.h>

Servo servo;

void setup() 
{
   Serial.begin(9600);
  servo.attach(2);  //D4
}

void loop() 
{
  servo.write(0);
  Serial.println(0);
  delay(5000);
  servo.write(90);
  Serial.println(90);
  delay(3000);
}
