/*
  MyStepMotor.h - Library for controlling 28BYJ48 step by step motor

*/
#ifndef MyStepMotor_h
#define MyStepMotor_h

#include "Arduino.h"

class MyStepMotor
{
public:
	// Turn on motor
	//    steps: Number of steps of 8*5.625/64 degrees
	//           512 steps is a whole circle
	//    mDirection: False: Clockwise; True: Counterclockwise
	//    mMotorSpeed: // in ms. Between 1 and 150 (the lower the faster)
	//    mType: 0 = simple; 1 = normal; 2 = halfpass
	void motor_on(int steps, bool mDirection, int mMotorSpeed, int mType);
	void motor_off();
	int GetPosition(); // Gets the position of the motor
	// constructor
	MyStepMotor(int IN1, int IN2, int IN3, int IN4);

private:
	int mIN1;				// Orange
	int mIN2;				// Yellow
	int mIN3;				// Pink
	int mIN4;				// Blue
	int mPosition;			// Position
	const int halfpass[8] = // Secuencia de pasos "medio paso"
		{
			B1000,
			B1100,
			B0100,
			B0110,
			B0010,
			B0011,
			B0001,
			B1001};
	const int simplepass[4] = // Simple pass. (más suave pero menos torque y retención)
		{
			B1100,
			B0110,
			B0011,
			B1001};
	const int normalpass[4] = // Normal pass. (Más usada y recomendada; Mayor torque y retención
		{
			B1100,
			B0110,
			B0011,
			B1001};
};

#endif