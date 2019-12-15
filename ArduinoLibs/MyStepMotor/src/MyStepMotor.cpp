/*
  MyStepMotor.cpp - Library for controlling 28BYJ48 step by step motor
*/

#include "Arduino.h"
#include "MyStepMotor.h"

// Constructor
//    IN1: First inductor (Orange)
//    IN2: Second inductor (Yellow)
//    IN3: Third inductor (Pink)
//    IN4: Fourth inductor (Blue)
MyStepMotor::MyStepMotor(int IN1, int IN2, int IN3, int IN4)
{
	this->mIN1 = IN1;
	this->mIN2 = IN2;
	this->mIN3 = IN3;
	this->mIN4 = IN4;
	this->mPosition = 0;
}

// Turn off motor
//    mIN1: First inductor (Orange)
//    mIN2: Second inductor (Yellow)
//    mIN3: Third inductor (Pink)
//    mIN4: Fourth inductor (Blue)
void MyStepMotor::motor_off()
{

	digitalWrite(mIN1, 0);
	digitalWrite(mIN2, 0);
	digitalWrite(mIN3, 0);
	digitalWrite(mIN4, 0);
}

// Turn on the motor
void MyStepMotor::motor_on(int steps, bool mDirection, int mMotorSpeed, int mType)
{

	for (int j = 0; j < steps; j++)
	{
		if (mType == 0) // Simple pass
		{
			for (int i = 0; i < 4; i++)
			{
				int step = i; // paso en sentido horario
				if (mDirection)
					step = 4 - i; // paso en sentido antihorario

				digitalWrite(mIN1, bitRead(simplepass[step], 0));
				delay(1);
				digitalWrite(mIN2, bitRead(simplepass[step], 1));
				delay(1);
				digitalWrite(mIN3, bitRead(simplepass[step], 2));
				delay(1);
				digitalWrite(mIN4, bitRead(simplepass[step], 3));
				delay(1);
				this->mPosition = this->mPosition + steps;
				if (this->mPosition > 511)
				{
					this->mPosition = this->mPosition - 512;
				}
				delay(mMotorSpeed); // Limita la velocidad de giro
			}
		}
		if (mType == 1) // Normal pass
		{
    		Serial.print("   Enable motor ");
			for (int i = 0; i < 4; i++)
			{
				int step = i; // paso en sentido horario
				if (mDirection)
					step = 4 - i; // paso en sentido antihorario

				digitalWrite(mIN1, bitRead(normalpass[step], 0));
    		    Serial.print("   Writing  pin ");
    		    Serial.print(mIN1);
    		    Serial.print(bitRead(normalpass[step],0));
    		    Serial.println();
				digitalWrite(mIN2, bitRead(normalpass[step], 1));
    		    Serial.print(mIN2);
    		    Serial.print(bitRead(normalpass[step],0));
    		    Serial.println();
				digitalWrite(mIN3, bitRead(normalpass[step], 2));
    		    Serial.print(mIN3);
    		    Serial.print(bitRead(normalpass[step],0));
    		    Serial.println();
				digitalWrite(mIN4, bitRead(normalpass[step], 3));
    		    Serial.print(mIN4);
    		    Serial.print(bitRead(normalpass[step],0));
    		    Serial.println();
				this->mPosition = this->mPosition + steps;
				if (this->mPosition > 511)
				{
					this->mPosition = this->mPosition - 512;
				}
				delay(mMotorSpeed); // Limita la velocidad de giro
			}
		}
		if (mType == 2) // Half pass
		{
			// HALF-PASS Secuencia de encendido de la bobinas (8 pasos por vuelta)
			for (int i = 0; i < 8; i++)
			{
				int step = i; // paso en sentido horario
				if (mDirection)
					step = 8 - i; // paso en sentido antihorario

				digitalWrite(mIN1, bitRead(halfpass[step], 0));
				digitalWrite(mIN2, bitRead(halfpass[step], 1));
				digitalWrite(mIN3, bitRead(halfpass[step], 2));
				digitalWrite(mIN4, bitRead(halfpass[step], 3));
				this->mPosition = this->mPosition + steps;
				if (this->mPosition > 511)
				{
					this->mPosition = this->mPosition - 512;
				}
				delay(mMotorSpeed); // Limita la velocidad de giro
			}
		}
		if (mType >= 2) // Half pass
		{
			Serial.println("Invalid type for the motor");
		}
	}
}

int MyStepMotor::GetPosition()
{
	return this->mPosition;
}