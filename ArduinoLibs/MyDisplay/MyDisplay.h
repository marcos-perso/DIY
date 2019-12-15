/*
  MyDisplay.h - My own library to control a 7-segment display (TM1637)

*/
#ifndef MyDisplay_h
#define MyDisplay_h

#include <TM1637.h>
#include "Arduino.h"

class MyDisplay
{
  public:
    void Display(int Number);
    // constructor
    MyDisplay(int CLK_PIN , int DIO_PIN);
  private:
  	int CLK_PIN; // Clock pin
  	int DIO_PIN; // Data pin
    TM1637 tm1637; 
};

#endif