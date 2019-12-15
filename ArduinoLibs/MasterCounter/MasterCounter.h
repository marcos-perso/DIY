/*
  MasterCounter.h - Counter that generates a loop number to be used by other modules

*/
#ifndef MasterCounter_h
#define MasterCounter_h

#include "Arduino.h"

class MasterCounter
{
public:
  // Get the number of iterations for the current period
  bool EstimateIterations();
  // constructor
  // Period = Period of the loop
  MasterCounter(uint32_t Period);
  // Initialize
  void Initialize();
  // Getters
  bool GetEnableMotor();
  bool GetEnableDisplay();
  bool GetEnableUltrasound();
  bool GetEnableJoystick();
  bool GetEnableSerialAndDebug();
  // Debug
  unsigned long GetCycleStart();
  uint32_t GetPeriod();

private:
  uint32_t NbIterations;    // Number of iterations for teh current period
  uint32_t Period;          // Period
  unsigned long CycleStart; // Enable of the cycle
  unsigned long Delta;      // Delta with the start of the cycle
  // Controls the tart the different entities
  bool EnableMotor;
  bool EnableDisplay;
  bool EnableUltrasound;
  bool EnableJoystick;
  bool EnableSerialAndDebug;
};

#endif