/*
  MyThermistor.h - My own library to control a thermistor (KY-013)
  		NTC Resistance to Kelvin conversion:
			1/K = 1/K0 + 1/B * ln(R/R0)
      where:
          K0: Nominal temperature
          R0: Nominal Resistence
*/

#include "MyThermistor.h"

// Constructor
//    THERMISTOR_PIN: PIN WHERE THE ADC FROM THE THERMISTOR IS CONNECTED
MyThermistor::MyThermistor(int THERMISTOR_INPUT)
{
	this->THERMISTOR_INPUT = THERMISTOR_INPUT;
  this->T_NOMINAL_K = this->CelsiusToKelvins(T_NOMINAL);

}

// Get the temperature from the thermistor
void MyThermistor::GetTemperature()
{

  Serial.println(F("Displaying temperature!")); // prints hello with ending line break

  // Calculate the resistence of the thermistor
  this->CalculateResistence();

  // Calculate the temperature (in Kelvins)
  this->CalculateAmbientTemperature();

  Serial.print("Temperature: "); 
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
  this->R_NTC = this->TH_R0 * ((1024.0 / (float)Vo) - 1.0); //calculate resistance on thermistor
  this->C_A = 1/(this->CelsiusToKelvins(this->T_NOMINAL_K));
  this->C_B = 1/this->B_VALUE;

}

void MyThermistor::CalculateAmbientTemperature()
{
  // Variables
  //float A = 0.003354;
  //float B = 0.00025346;

  // Calculate the ambient temperature
  this->T_AMBIENT = (1.0 / (this->C_A + this->C_B*log(this->R_NTC/this->R_NOMINAL)) ); // temperature in Kelvin
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
  T_K = T_C + 273.15; //convert Kelvin to Celcius
  return T_K; //convert Kelvin to Celcius
}