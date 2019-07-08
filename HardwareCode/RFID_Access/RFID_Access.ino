/*
 *  Created by The Agents of SHIELD
*/

#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#define RED_LED 16  // D0
#define GREEN_LED 0 // D3

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "EC5";
const char* password = "123456789";
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
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() 
{
  servo.attach(2);//D4
  pinMode(GREEN_LED,OUTPUT);   //TX Grenn LED
  pinMode(RED_LED,OUTPUT);   // Red Light

  digitalWrite(GREEN_LED,LOW);  //Green OFF
  digitalWrite(RED_LED,HIGH);  //Red ON
  servo.write(90);  // gate closed
  delay(1000);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  msg = "Welcome to Intelli Toll gate!";
  client.publish("outTopic007", msg);
  
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

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic008");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
// test by raj
void loop() 
{
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
  
  if (content.substring(1) == "35_3C_B1_15") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    msg = "Access Granted. You can Go!";
    client.publish("outTopic007", msg);
    Serial.println("You can go!");
    servo.write(0); //Gate open
    digitalWrite(GREEN_LED,HIGH); // Green Light ON //Tx
    digitalWrite(RED_LED,LOW);  // Red OFF    //Rx
    delay(10000);
    digitalWrite(GREEN_LED,LOW);  //Green OFF
    digitalWrite(RED_LED,HIGH);   //Red ON
    servo.write(90);  //gate Closed
    Serial.println("Next Please!");
    //Serial.println();
    statuss = 1;
  }
  else   
  {
    Serial.println(" Access Denied ");
    digitalWrite(GREEN_LED,LOW);  //Green OFF
    digitalWrite(RED_LED,HIGH);  //Red ON
    msg = "Access Denied!";
    client.publish("outTopic007", msg);
    delay(3000);
  }
} 
