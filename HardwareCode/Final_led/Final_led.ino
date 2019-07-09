#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <FirebaseArduino.h>
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F, 16, 2);

const char* ssid = "HAWELI";
const char* password = "keshav.raj06";
const char* mqtt_server = "iot.eclipse.org";
 
char *msg;
Servo servo;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() 
{
  delay(5);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
String cardNumber;
int payStatus;
void setup() {
  
  servo.attach(15);//D8
  servo.write(0);
  delay(1000);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  setup_wifi();
  //Wire.begin(2,0);
  //lcd.begin();   // initializing the LCD
  //lcd.backlight(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  msg = "Welcome to Intelli Toll gate!";
    client.publish("outTopic007", msg);
  //connecting firebase
  Firebase.begin("intellitollgate.firebaseio.com","YiACACoSmOgUEnkYY3s8FNijEoAtkkvabOTX2C51");  
  cardNumber=Firebase.getString("CARD_NUMBER/nLrJ6QBB1fZdmvIchc3ziqqiyqM2");
  Serial.println(cardNumber);
 // payStatus=Firebase.getInt("PAY_STATUS/nLrJ6QBB1fZdmvIchc3ziqqiyqM2");
  pinMode(2,OUTPUT);
  pinMode(0,OUTPUT);
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic008");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {

  //cardNumber=Firebase.getString("CARD_NUMBER/pjtKHpOjkYREQZLiZD7TiDJgokb2");
//  Serial.println(cardNumber);
 // lcd.clear();
  //lcd.print("N.I.C.E Road!!!");
  digitalWrite(0,HIGH);
     if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
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
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "_");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "_"));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  //cardNumber=Firebase.getString("CARD_NUMBER/pjtKHpOjkYREQZLiZD7TiDJgokb2");
  //Serial.println(cardNumber);
  
  if (content == cardNumber) //change UID of the card that you want to give access
  {
    payStatus=Firebase.getInt("PAY_STATUS/nLrJ6QBB1fZdmvIchc3ziqqiyqM2");
    if(payStatus==1){
      digitalWrite(0,LOW);
      digitalWrite(2,HIGH);
      Serial.println(" Access Granted ");
    //  lcd.clear();
     // lcd.print("Access Granted!!!");
      msg = "Access Granted. You can Go!";
      client.publish("outTopic007", msg);
      Serial.println("You can go!");
      servo.write(90);
      delay(10000);
      servo.write(0);
      Serial.println("Next Please!");
      //lcd.clear();
      //lcd.print("Next!!!");
      //delay(5000);
      //lcd.clear();
      //lcd.print("N.I.C.E Road!!!");
    //Serial.println();
      statuss = 1;
      digitalWrite(2,LOW);
      digitalWrite(0,HIGH);
    }
    else
    {
      Serial.println("Payment not yet done!!!");
      //lcd.clear();
      //lcd.print("Not Paid");
      delay(5000);
    }
  }
  else   
  {
    Serial.println(" Access Denied ");
    //lcd.clear();
    //lcd.print("Bharwa Vaibhav");
    msg = "Access Denied!";
    client.publish("outTopic007", msg);
    delay(3000);
  }

}
