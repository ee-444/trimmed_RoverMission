
//PID control code by Tim Hirzel
//modified by Misael Espinoza
//This module implements a PID control loop initializes it with 3 values: p, i, d
//and then tunes the feedback loop with the setP, setI, setD functions

#include "pid.h"

unsigned int timeCount = 0;

// variables used in asjustment
float iState = 0;
float lastHeading = 0;
float pTerm, iTerm, dTerm;
// constants used in adjustment
const float pgain = 0.9;
const float igain = 0.01;
const float dgain = 1.0;
const float WINDUP_GUARD_GAIN = 100.0;

float updatePID(float targetHeading, float curHeading)
{
	double result;
	float error;
	float windupGuard;

	//determine error
	error = targetHeading - curHeading;

	//limit rotation
	if(error > 1800){
		error -= 3600;
	}
	else if (error < -1800){
		error += 3600;
	}

	/*---------------PROPORTIONAL---------------*/
	//the pTerm is the present, it is the instantaneous error
	pTerm = pgain * error;
	/*---------------PROPORTIONAL---------------*/

	/*---------------INTEGRAL---------------*/
	//iState is the past, it is the accumulated error over time
	iState += error;

	//Windup guard, if the robot is turned completely around, this prevents
	//it from not being able to correct itself

	//make windup guard values relative to current iGain
	windupGuard = WINDUP_GUARD_GAIN / igain;

	if(iState > windupGuard){//protects against excessive positive error
		iState = windupGuard;
	}
	else if(iState < -windupGuard){//protects against excessive negative error
		iState = -windupGuard;
	}

	//accumulated error multiplied by the gain determine the iTerm
	iTerm = igain * iState;
	/*---------------INTEGRAL---------------*/

	/*---------------DERIVATIVE---------------*/
	//The dTerm is the future, it is the rate at which the heading is changing
	dTerm = (dgain * (curHeading - lastHeading));

	//store the current temperature
	lastHeading = curHeading;

	//feedback
	return pTerm + iTerm - dTerm;
}
