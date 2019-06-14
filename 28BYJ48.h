/*
 * 28BYJ48.h
 * 28BYJ-48 stepper motor driving library, using motor driver based on ULN2003.
 * This library is compatible with arduino pro mini, nano, and uno boards.
 * Driver wiring possibilities:
 * 	1: pins 2,3,4,5			timer0
 *  2: pins 6,7,8,9			timer0
 *  3: pins 10,11,12,13 	timer2
 *  4: pins A0, A1, A2, A3		timer2
 * It uses Timer 0 and 2
 * author: Attila Medgyesi
 * email: medgyesiatila1998@gmail.com
 * date: 
 */

 
#ifndef __28BYJ48__H__ 
#define __28BYJ48__H__

#include "Arduino.h"

//#define DEBUG
#ifndef DEBUG
	#define LOG(x) 
	#define LOG_INIT(x) 
#else 
	#define LOG(x) (Serial.print(x))
	#define LOG_INIT(x) (Serial.begin(x))
#endif


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
 