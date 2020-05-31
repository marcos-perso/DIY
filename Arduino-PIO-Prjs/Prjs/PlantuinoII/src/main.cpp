// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include "WiFi.h"
#include "HardwareSerial.h"

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

// ###############
// ### OBJECTS ###
// ###############
//HardwareSerial Serial2(2);


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
  }
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
 
 
}

// ############
// ### LOOP ###
// ############
 
void loop() {

  Serial2.println(F("Marcos1"));
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
  digitalWrite(LED_PIN,LOW);
  delay(1000);
}