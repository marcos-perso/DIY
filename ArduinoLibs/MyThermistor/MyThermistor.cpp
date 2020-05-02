/*
  MyThermistor.h - My own library to control a thermistor (KY-013)
  		NTC Resistance to Kelvin conversion:
			1/K = 1/K0 + 1/B * ln(R/R0)
      where:
          K0: Nominal temperature
          R0: Nominal Resistence

      KY-013 connections
      S pin --> To Arduino
      M pin --> VCC
      - pin --> GND

      R(S/-) = RNTC
      R(S/M) = R0
*/

#include "MyThermistor.h"

// Constructor
//    THERMISTOR_PIN: PIN WHERE THE ADC FROM THE THERMISTOR IS CONNECTED
MyThermistor::MyThermistor(int THERMISTOR_INPUT)
{
	this->THERMISTOR_INPUT = THERMISTOR_INPUT;

}

// Get the temperature from the thermistor
void MyThermistor::GetTemperature()
{

  Serial.println(F("Displaying temperature!"));

  // Calculate the resistence of the thermistor
  this->CalculateResistence();

  // Calculate the temperature (in Kelvins)
  this->CalculateAmbientTemperature();

  Serial.print(F("Temperature: ")); 
  Serial.print(this->KelvinsToCelsius(this->T_AMBIENT));
  Serial.println(" C"); 

}

// Calculate the temperature from the sensor
void MyThermistor::CalculateResistence()
{

  // Variables
  int Vo;

  // Read the voltage from the sensor
  Vo = analogRead(this->THERMISTOR_INPUT);

  // Calculate the resistence of the NTC
  this->R_NTC = this->TH_R0 / ((1023.0 / (float)Vo) - 1.0); //calculate resistance on thermistor

}

void MyThermistor::CalculateAmbientTemperature()
{
  // Calculate the ambient temperature
  this->T_AMBIENT = (1.0 / (this->C_A + logf(this->R_NTC/this->R_NOMINAL)/this->B_VALUE) ); // temperature in Kelvin
}

//! \brief This method converts from Celsius to Kelvins
// @param[in] T_K Temperature in Kelvins 
// @return Temperature in Celsius 
double MyThermistor::KelvinsToCelsius(double T_K)
{
  double T_C;
  T_C = T_K - 273.15; //convert Kelvin to Celcius
  return T_C; //convert Kelvin to Celcius
}

//! \brief This method converts from Celsius to Kelvins
// @param[in] T_C Temperature in Celsius 
// @return Temperature in Kelvins 
double MyThermistor::CelsiusToKelvins(double T_C)
{
  double T_K;
  T_K = T_C + 273.15; //convert Kelvin to Celsius
  return T_K; //convert Celsius to Kelvins
}