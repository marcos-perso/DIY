/*
  MyUltrasoundSensor.cpp - My own library to control an ultrasound sensor
  A maximum of 50 cm is set
  Duration of the measurement: Between 12 and 261,92+12= 273,92 us
*/

#include "Arduino.h"
#include "MyUltrasoundSensor.h"

// Constructor
//    CLK: Clock
//    DIO: Data
MyUltrasoundSensor::MyUltrasoundSensor(int TRIGGER_PIN , int ECHO_PIN)
{
	this->TRIGGER_PIN = TRIGGER_PIN;
	this->ECHO_PIN = ECHO_PIN;

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

}

// UltrasoundSensor measurement
// Units: False = inches; True = cm
long MyUltrasoundSensor::Measure(bool Units)
{

  long cm;
  long inches;
  long duration;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH,this->USTimeOut);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135

  if (Units)
  {
    return cm;
  } else {
    return inches;
  }

}
