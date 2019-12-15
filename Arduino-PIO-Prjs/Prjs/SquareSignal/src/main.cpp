/*
* #####################
* ### SQUARE SIGNAL ###
* #####################
*/
// This program generates a simple square signal
// to allow testing the oscilloscope

// ################
// ### INCLUDES ###
// ################

#include "Arduino.h"

// ############
// ### PINS ###
// ############

// Pins towards the oscilloscope
#define SQUARE_OUT 8

// #################
// ### CONSTANTS ###
// #################

uint32_t Period = 200; // Period in ms

// #################
// ### VARIABLES ###
// #################
bool State;

// ###############
// ### OBJECTS ###
// ###############

// #############
// ### SETUP ###
// #############

void setup()
{

  // Setrial communication
  Serial.begin(9600);                // set up Serial library at 9600 bps
  Serial.println(F("Hello Square!")); // prints hello with ending line break

  State = false;

}

// ############
// ### LOOP ###
// ############

void loop()
{

if (State)
{
	digitalWrite(SQUARE_OUT, 1);
} else {
	digitalWrite(SQUARE_OUT, 0);
}
State = !State;

  delay(Period);

}