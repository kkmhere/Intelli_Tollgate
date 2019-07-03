#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

// Set these to run example.

#define FIREBASE_HOST "fir-app-example.firebaseio.com"
#define FIREBASE_AUTH "examplesd2asdasdasdasd2asd3asd2asd2as32das3d2as2da3"
#define WIFI_SSID "Wifi Router Name"
#define WIFI_PASSWORD "Router Password"
#define LED 2

void setup() 
{
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LEDStatus",0);
}

void loop() 
{
  if(Firebase.getInt("LEDStatus"))
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  if (Firebase.failed()) // Check for errors 
  {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);
}
