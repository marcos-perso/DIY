//#include <TM1637.h>
#include <MyStepMotor.h>
#include <MyDisplay.h>
#include <MyUltrasoundSensor.h>
#include <MasterCounter.h>

//## Probando

/*
* ################
* ### My Robot ###
* ################
*/
// The distribution of the timing will be as follows:
// Period of 200 ms (5 Hz)
//    0-10 ms    (100 ms) ==> Start process (launched at the beginning of each cycle)
//    10-100 ms  (90 ms)  ==> Motor handling
//    100-120 ms (20 ms)  ==> Display handling
//    120-170 ms (20 ms)  ==> US
//    170-180 ms (20 ms)  ==> Joystick
//    180-200 ms (20 ms)  ==> Serial communication & debug
// The timing is controlled by MasterCounter. A signal is sent to each of the modules

// ############
// ### PINS ###
// ############

// Pins towards the motor
#define motor_IN1 8
#define motor_IN2 9
#define motor_IN3 10
#define motor_IN4 11

// 7-segments
const int TM1637_CLK = 13; //pins definitions for TM1637 and can be changed to other ports
const int TM1637_DIO = 12;

// Ultrasounds
#define SR05_TRIG 6
#define SR05_ECHO 7

// Joystick
const int JoystickX = A0;

// #################
// ### CONSTANTS ###
// #################

int8_t NumTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //0~9,A,b,C,d,E,F
uint32_t Period = 200;                                                    // Period in ms

// #################
// ### VARIABLES ###
// #################

bool CycleStarted;
bool Initial;
bool MotorOn = false; // Control activity of the motor
int MotorSpeed = 5;
long cm;
int xPos = 0;
uint32_t NbIterations = 0; // Number of loops

// ###############
// ### OBJECTS ###
// ###############

// Master Counter object
MasterCounter Counter(Period);
// Motor object
//MyStepMotor MyMotor(motor_IN1, motor_IN2, motor_IN3, motor_IN4);
MyStepMotor MyMotor(motor_IN1, motor_IN2, motor_IN3, motor_IN4);
// Display object
MyDisplay Display(TM1637_CLK, TM1637_DIO);
// Ultrasound object
MyUltrasoundSensor UltrasoundSensor(SR05_TRIG, SR05_ECHO);

// #############
// ### SETUP ###
// #############

void setup()
{

  // Serial communication
  Serial.begin(9600);                // set up Serial library at 9600 bps
  Serial.println(F("Hello world!")); // prints hello with ending line break

  Counter.Initialize();

  // Program pins for the motor
  pinMode(motor_IN1, OUTPUT);
  pinMode(motor_IN2, OUTPUT);
  pinMode(motor_IN3, OUTPUT);
  pinMode(motor_IN4, OUTPUT);

  pinMode(JoystickX, INPUT);

  // Initialize Cycles
  CycleStarted = false;
  Initial = true;

  // Initialize Motor
  MotorOn = true;
}

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

uint16_t getFreeSram()
{
  uint8_t newVariable;
  // heap is empty, use bss as start memory address
  if ((uint16_t)__brkval == 0)
    return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
  // use heap end as the start of the memory address
  else
    return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
};

// ############
// ### LOOP ###
// ############

void loop()
{

  // Run MasterCounter
  CycleStarted = Counter.EstimateIterations();

  if (Initial || CycleStarted)
  {
    Initial = false;
    MotorOn = true;
    //Serial.print("Cycle START = ");
    //Serial.println(Counter.GetCycleStart());
  }

  // Update motors (one step)
  if (Counter.GetEnableMotor())
  {
    if (MotorOn)
    {
      MotorOn = false;
      if (xPos > 1000)
      {
      MyMotor.motor_on(5, false, 1,0);
      //Serial.print("   EnableMotor at: ");
      //Serial.println(millis());
      }
      if (xPos < 500)
      {
      MyMotor.motor_on(-5, false, 1,0);
      //Serial.print("   EnableMotor at: ");
      //Serial.println(millis());
      }
    }
  }

  // Show display
  if (Counter.GetEnableDisplay())
  {
    Display.Display(MyMotor.GetPosition());
    //Serial.print("   Enable Display at: ");
    //Serial.println(millis());
  }

  // Read sensors (MAX = 300 ms)
  if (Counter.GetEnableUltrasound())
  {
    cm = UltrasoundSensor.Measure(true);
    //Serial.print("   Enable US at: ");
    //Serial.println(millis());
  }

  // Communicate data to terminal
  // Joystick
  if (Counter.GetEnableJoystick())
  {
    xPos = analogRead(JoystickX);
    //Serial.print("   Enable JS at: ");
    //Serial.print(millis());
    //Serial.print(" - ");
    //Serial.println(xPos);
  }

  if (Counter.GetEnableSerialAndDebug())
  {
    //Serial.print("   Enable Serial and Debugger at: ");
    //Serial.println(millis());
  }

}