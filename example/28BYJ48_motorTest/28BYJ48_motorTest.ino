/*
 * 28BYJ-48 stepper motor driving example
 * 
 * Using:
 * 28BYJ-48 stepper motor driving library, using motor driver based on ULN2003.
 * This library is compatible with arduino pro mini, nano, and uno boards.
 * Driver wiring possibilities:
 * 	1: pins 2,3,4,5			timer0
 *  2: pins 6,7,8,9			timer0
 *  3: pins 10,11,12,13 	timer2
 *  4: pins A0, A1, A2, A3		timer2
 * It uses Timer 0 and 2
 * 
 * author: Attila Medgyesi
 * email: medgyesiatila1998@gmail.com
 * date: 
 */
//#define DEBUG
#include <28BYJ48.h>

StepperMotor_28BYJ48 motor1(3);//select pin configuration
StepperMotor_28BYJ48 motor2(4);//select pin configuration
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
 if(!motor2.init())    
  {
    Serial.println("Pin configuration already used");
    while(1);
  }
	Serial.println("Init end");
	motor1.drive(5);
  motor2.drive(5, DIRECTION_BACKWARD);
	//motor1.changeDefaultDirection(DIRECTION_BACKWARD);
	
}

void loop()
{
	
		
		
	
 
	/*motor1.stop();
 
  

		motor1.drive(7, DIRECTION_BACKWARD);
		
	
	motor1.stop();
	motor1.driveSteps(100, 4);
  Serial.println(TCNT2);*/
	
}
	