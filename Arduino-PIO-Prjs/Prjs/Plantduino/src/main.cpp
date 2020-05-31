// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include <MyThermistor.h>
#include "SoftwareSerial.h"

// ###################
// ### Description ###
// ###################

// Arduino plant controller. It implements
//    --> Sense temperature and send it to a remote GUI (mobile) 

// ############
// ### PINS ###
// ############
#define THERMISTOR_PIN A0

// #################
// ### CONSTANTS ###
// #################
#define TH_R0 10000 // Value of the thermistor resistence


// #################
// ### VARIABLES ###
// #################


// ###############
// ### OBJECTS ###
// ###############
MyThermistor i_Thermistor(THERMISTOR_PIN);
SoftwareSerial softSerial(2, 3); // RX, TX

// #############
// ### SETUP ###
// #############
void setup() {

  pinMode(THERMISTOR_PIN, INPUT);

  // put your setup code here, to run once:
  // Serial communication
  Serial.begin(9600);     // Serial Link through USB
  //softSerial.begin(115200); // Serial link to WiFi
  softSerial.begin(9600); // Serial link to WiFi
  Serial.println(F("Hello world!")); // prints hello with ending line break
    delay(1000);
}

// ############
// ### LOOP ###
// ############

void loop() {
  // put your main code here, to run repeatedly:
  //i_Thermistor.GetTemperature();
 
// enviar los datos de la consola serial al ESP-01, 
// y mostrar lo enviado por el ESP-01 a nuestra consola
 
  char ReceivedSerial;
   if (softSerial.available())
   {
      Serial.print((char)softSerial.read());
   }
   if (Serial.available())
   {
    ReceivedSerial = Serial.read();
      //Serial.print(ReceivedSerial);
      softSerial.print(ReceivedSerial);
   }

}