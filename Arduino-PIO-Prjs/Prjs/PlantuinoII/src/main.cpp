// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include "WiFi.h"
//##include "ESP8266WiFi.h"
#include "EEPROM.h"
#include "PubSubClient.h"

// ###################
// ### Description ###
// ###################

// Arduino plant controller. It implements
//    --> Sense temperature and send it to a remote GUI (mobile) 

// ############
// ### PINS ###
// ############

// LED
#define LED_PIN 23
// UART CONNECTION
#define UART2_RX 16
#define UART2_TX 17

// #################
// ### CONSTANTS ###
// #################
#define EEPROM_SIZE 64 // We retrieve 64 bytes from flash

// #################
// ### VARIABLES ###
// #################

char ssid[20];
char password[20];
char mqtt_server[20];

// ###############
// ### OBJECTS ###
// ###############
WiFiClient espClient;
PubSubClient client(espClient);


// #################
// ### FUNCTIONS ###
// #################

//String translateEncryptionType(wifi_auth_mode_t encryptionType) {
// 
//  switch (encryptionType) {
//    case (WIFI_AUTH_OPEN):
//      return "Open";
//    case (WIFI_AUTH_WEP):
//      return "WEP";
//    case (WIFI_AUTH_WPA_PSK):
//      return "WPA_PSK";
//    case (WIFI_AUTH_WPA2_PSK):
//      return "WPA2_PSK";
//    case (WIFI_AUTH_WPA_WPA2_PSK):
//      return "WPA_WPA2_PSK";
//    case (WIFI_AUTH_WPA2_ENTERPRISE):
//      return "WPA2_ENTERPRISE";
//    case (WIFI_AUTH_MAX):
//      return "TBD";
//  }
//
//  return "Done";
//}
 
void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Encryption type: ");
    //String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    //Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
 
  }
}
 
void connectToNetwork(char * _ssid, char* _password) {

  WiFi.begin(_ssid, _password);

  Serial2.print(F("Connecting to network1 "));
  Serial2.println(_ssid);
  Serial2.println(_password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial2.println("Establishing connection to WiFi..");
  }
 
  Serial2.println("Connected to network");
 
}

// Callback when receiving MQTT topic

void callback(char* topic, byte* message, unsigned int length) {
  Serial2.print("Message arrived on topic: ");
  Serial2.print(topic);
  Serial2.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial2.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial2.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "Marcos") {

    Serial2.print("Changing output to ");
    if(messageTemp == "on"){
      Serial2.println("on");
      digitalWrite(LED_PIN, HIGH);
    }
    else if(messageTemp == "off"){
      Serial2.println("off");
      digitalWrite(LED_PIN, LOW);
    }
  }
}

// Reconnect to MQTT broker
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial2.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("PlantuinoII","PlantuinoII","pw-PlantuinoII")) {
      Serial2.println("connected");
      // Subscribe
      client.subscribe("Marcos");
    } else {
      Serial2.print("failed, rc=");
      Serial2.print(client.state());
      Serial2.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// #############
// ### SETUP ###
// #############
 
void setup() {

  // PINOUT
  pinMode(LED_PIN, OUTPUT);

  // Start serial communications
  Serial.begin(9600);
  //Serial2.begin(9600);
  Serial2.begin(115200,SERIAL_8N1,UART2_RX,UART2_TX);

  // Get Wi-Fi credentials from flash
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0,ssid);
  EEPROM.get(16,password);
  //EEPROM.get(32,mqtt_server);
  // Set the value of teh IP of the broker
  strcpy(mqtt_server, "node02.myqtthub.com");


  // Connect to Wi-Fi network
  //scanNetworks();
  Serial2.print(F("Connecting to network "));
  Serial2.println(ssid);
  connectToNetwork(ssid, password);
 
  Serial2.println(WiFi.macAddress());
  Serial2.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
 
}

// ############
// ### LOOP ###
// ############
 
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(1000);

//  digitalWrite(LED_PIN,HIGH);
//  delay(1000);
//  digitalWrite(LED_PIN,LOW);

//  client.publish("home", "Marcos");

}