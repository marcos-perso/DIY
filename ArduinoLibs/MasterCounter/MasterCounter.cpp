/*
  MasterCounter.cpp - Counter that generates a loop number to be used by other modules
*/

#include "Arduino.h"
#include "MasterCounter.h"

// Constructor
MasterCounter::MasterCounter(uint32_t Period)
{
  this->Period = Period;
}

// Returns true if teh cycle is starting
bool MasterCounter::EstimateIterations()
{

  bool CycleStarted = false;

  // Reset all EnableX
  EnableMotor = false;
  EnableDisplay = false;
  EnableJoystick = false;
  EnableSerialAndDebug = false;

  this->Delta = millis() - this->CycleStart;

  // Check if we update the cycle start
  if (this->Delta >= this->Period)
  {
    this->NbIterations++;
    CycleStarted = true;
    this->CycleStart = millis();
  }

  // Now we check in which part of the cycle we are
  if ((this->Delta >= 10) && (this->Delta <= 100)) { EnableMotor = true; }
  if ((this->Delta >= 100) && (this->Delta <= 120)) { EnableDisplay = true; }
  if ((this->Delta >= 120) && (this->Delta <= 170)) { EnableUltrasound = true; }
  if ((this->Delta >= 170) && (this->Delta <= 180)) { EnableJoystick = true; }
  if ((this->Delta >= 180) && (this->Delta <= 200)) { EnableSerialAndDebug = true; }

  return CycleStarted;

}

// Initializes the counter
void MasterCounter::Initialize()
{
	this->NbIterations = 0;
  this->CycleStart = 0;
}

// Getters
bool MasterCounter::GetEnableMotor() { return this->EnableMotor; }
bool MasterCounter::GetEnableDisplay() { return this->EnableDisplay; }
bool MasterCounter::GetEnableUltrasound() { return this->EnableUltrasound; }
bool MasterCounter::GetEnableJoystick() { return this->EnableJoystick; }
bool MasterCounter::GetEnableSerialAndDebug() { return this->EnableSerialAndDebug; }

// Debug
unsigned long MasterCounter::GetCycleStart()
{
  return this->CycleStart;
}
// Debug
uint32_t MasterCounter::GetPeriod()
{
  return this->Period;
}
