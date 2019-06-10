/*
 * 28BYJ48.h
 * 28BYJ-48 stepper motor driving library, using motor driver based on ULN2003.
 * This library is compatible only with arduino pro micro board.
 * Driver wiring possibilities:
 * 	1: pins 2,3,4,5			timer1
 *  2: pins 6,7,8,9			timer3
 *  3: pins 10,16,14,15 	timer3
 *  4: pins 18,19,20,21		timer1
 * It uses Timer 1 and 3
 * author: Attila Medgyesi
 * email: medgyesiatila1998@gmail.com
 * date: 
 */

 
#ifndef __28BYJ48__H__ 
#define __28BYJ48__H__

#include "Arduino.h"

#define DIRECTION_FORWARD true
#define DIRECTION_BACKWARD false

class StepperMotor_28BYJ48{
 private:
	char configuration;   					//selected wiring 1 to 4
	static bool selectedConfigurations[4];		//true, if corresponding wiring is selected once
	bool direction;							
	bool defaultDirection=DIRECTION_FORWARD;
	int steps;
	char microstep;
	
 public:
 	static StepperMotor_28BYJ48* pActivatedConfiguration[4];
	
 public:
	StepperMotor_28BYJ48(char configuration);
	bool init();
	void changeDefaultDirection(bool direction);
	void drive(unsigned char speed, bool direction=DIRECTION_FORWARD);   //speed 0 to 8
	void driveSteps(int steps, unsigned char speed, bool direction=DIRECTION_FORWARD);
	void stop();
	static StepperMotor_28BYJ48* getMotor(int num);
	void microStep();
	
	
	
};

#endif //__28BYJ48__H__
 