// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include <MyThermistor.h>

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

// #############
// ### SETUP ###
// #############
void setup() {

  pinMode(THERMISTOR_PIN, INPUT);

  // put your setup code here, to run once:
  // Serial communication
  Serial.begin(9600);                // set up Serial library at 9600 bps
  Serial.println(F("Hello world!")); // prints hello with ending line break
}

// ############
// ### LOOP ###
// ############

void loop() {
  // put your main code here, to run repeatedly:
  i_Thermistor.GetTemperature();
  delay(1000);
}