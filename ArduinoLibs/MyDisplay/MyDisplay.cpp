/*
  MyDisplay.cpp - My own library to control a 7-segment display (TM1637)
*/

#include "Arduino.h"
#include "MyDisplay.h"

// Constructor
//    CLK: Clock
//    DIO: Data
MyDisplay::MyDisplay(int CLK_PIN , int DIO_PIN) : tm1637(CLK_PIN, DIO_PIN)
{
	this->CLK_PIN = CLK_PIN;
	this->DIO_PIN = DIO_PIN;

  	tm1637.init();
  	tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

}

// Display an integer on the screen
void MyDisplay::Display(int Number)
{
    // Show display
    String sNumber = String(Number);
    sNumber.length();
    //this->tm1637.display(0,12);
    for (int i = 4- sNumber.length(); i < 4; i++)
    {
      tm1637.display(i,(String(sNumber.charAt(i-(4 -sNumber.length()))).toInt()));
    }

}
