// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"

// ###################
// ### Description ###
// ###################

// Arduino plant controller. It implements
//    --> Sense temperature and send it to a remote GUI (mobile) 

// ############
// ### PINS ###
// ############
#define LED_PIN 23
#define UART2_RX 16
#define UART2_TX 17

// #################
// ### CONSTANTS ###
// #################

// #################
// ### VARIABLES ###
// #################
const char* ssid = "YM-IoT";
const char* password = "Zumarraga0001";
const char* mqtt_server = "192.168.8.103";

// ###############
// ### OBJECTS ###
// ###############
WiFiClient espClient;
PubSubClient client(espClient);


// #################
// ### FUNCTIONS ###
// #################

String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
    case (WIFI_AUTH_MAX):
      return "TBD";
  }

  return "Done";
}
 
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
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
 
  }
}
 
void connectToNetwork() {
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }
 
  Serial.println("Connected to network");
 
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
    if (client.connect("ESP32Client")) {
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
 
  Serial.begin(9600);
  //Serial2.begin(115200,UART2_RX,UART2_TX);
  Serial2.begin(115200,SERIAL_8N1,UART2_RX,UART2_TX);
 
  //scanNetworks();
  connectToNetwork();
 
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

 // Serial2.println(F("Marcos1"));
//  digitalWrite(LED_PIN,HIGH);
//  delay(1000);
//  digitalWrite(LED_PIN,LOW);
//  delay(1000);

//  client.publish("home", "Marcos");

}