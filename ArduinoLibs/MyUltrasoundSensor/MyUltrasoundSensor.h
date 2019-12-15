/*
  MyUltrasoundSensor.h - My own library to control an ultrasound sensor (SR05)
  Parameters:
       USTimeOut: TimeOut for the sensor.
  Other:
       Dist(cm) = [Duration(us)/2]/34

*/
#ifndef MyUltrasoundSensor_h
#define MyUltrasoundSensor_h

#include "Arduino.h"

class MyUltrasoundSensor
{
  public:
    // UltrasoundSensor measurement
    // Units: False = inches; True = cm
    long Measure(bool Units);
    unsigned long USTimeOut =  5000; //Corresponds to a max distance of  approx 30cm
    // constructor
    MyUltrasoundSensor(int TRIGGER_PIN , int ECHO_PIN);
  private:
  	int TRIGGER_PIN; // Trigger pin
  	int ECHO_PIN; // Echo pin
};

#endif