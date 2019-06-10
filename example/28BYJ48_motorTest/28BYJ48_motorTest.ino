/*
 * 28BYJ-48 stepper motor driving example
 * 
 * Using:
 * 28BYJ-48 stepper motor driving library, using motor driver based on ULN2003.
 * This library is compatible only with arduino pro micro board.
 * Driver wiring possibilities:
 * 	1: pins 2,3,4,5			timer1
 *  2: pins 6,7,8,9			timer3
 *  3: pins 10,16,14,15 	timer3
 *  4: pins 18,19,20,21		timer1
 * It uses Timer 1 and 3
 * 
 * 
 * author: Attila Medgyesi
 * email: medgyesiatila1998@gmail.com
 * date: 
 */
 
#include <28BYJ48.h>

StepperMotor_28BYJ48 motor1(1);//select pin configuration

void setup()
{
	Serial.begin(9600);
	
	Serial.println("Stepper motor example test code");
	Serial.println("Init begin");
	
	if(!motor1.init()) 		
	{
		Serial.println("Pin configuration already used");
		while(1);
	}
	Serial.println("Init end");
	
	//motor1.changeDefaultDirection(DIRECTION_BACKWARD);
	
}

void loop()
{
	for(int i=0; i<8;i++)
	{
		motor1.drive(i);
		delay(4000);
	}
	motor1.stop();
	for(int i=0; i<8;i++)
	{
		motor1.drive(i, DIRECTION_BACKWARD);
		delay(4000);
	}
	motor1.stop();
	motor1.driveSteps(100, 4);
	delay(10000);
}
	
