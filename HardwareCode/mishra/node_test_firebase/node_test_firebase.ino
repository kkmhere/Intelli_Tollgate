#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>



const char* ssid = "HAWELI";
const char* pass = "keshav.raj06";
String value;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("CONNECTED");
 
  Firebase.begin("intellitollgate.firebaseio.com","YiACACoSmOgUEnkYY3s8FNijEoAtkkvabOTX2C51");
  //String path="https://console.firebase.google.com/u/0/project/intellitollgate/database/intellitollgate/data/CARD_NUMBER/LH6jrHKpHlXN7WimYTMw0sTvcEo1";
  //FirebaseObject object=Firebase.get(path);
  //String value;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("done");
  Firebase.setFloat("number", 100.0); 
  value=Firebase.getString("TEST1");
  Serial.println(value);
}
