/*
  MyThermistor.h - My own library to control a thermistor (KY-013)

*/
#ifndef MyThermistor_h
#define MyThermistor_h

#include "Arduino.h"

class MyThermistor
{
  public:
    // constructor
    MyThermistor(int THERMISTOR_INPUT);
  public:
    void GetTemperature();
  private:
    void CalculateAmbientTemperature();
    void CalculateResistence();
    double KelvinsToCelsius(double T_K);
    double CelsiusToKelvins(double T_K);
  private:
    // Constants
  	int THERMISTOR_INPUT; // Thermistor pin
    const int TH_R0 = 10000; // Thermistor module resistence 
    const float T_NOMINAL = 25; // Nominal temperature as provided by the datasheet (Celsius)
    const float R_NOMINAL = 100000; // Nominal resistence as provided by the datasheet (ohms)
    const int B_VALUE = 3950; // B Value for this Thermistor
    // Members
    double R_NTC; // Resistence of the NTC at this temperature
    double T_AMBIENT; // Ambient temperature calculated
    float C_A,C_B; // First coefficients of the temperature calculation
    float T_NOMINAL_K; // Nominal temperatur in Kelvins
};

#endif