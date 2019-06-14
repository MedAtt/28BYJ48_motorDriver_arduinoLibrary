#include "28BYJ48.h"


StepperMotor_28BYJ48* StepperMotor_28BYJ48::pActivatedConfiguration[4]={0};

StepperMotor_28BYJ48::StepperMotor_28BYJ48(char configuration)
{
	LOG_INIT(9600);
	LOG("Constructor");
	this->configuration=configuration;
}
bool StepperMotor_28BYJ48::init()
{
	if(configuration<1 || configuration>4) return false;
	if(pActivatedConfiguration[configuration-1]!=NULL) return false;
	
	pActivatedConfiguration[configuration-1]=this;
	
	if(configuration==1)	//PD2, PD3, PD4, PD5   timer0B
	{
		DDRD|=(1<<5)|(1<<4)|(1<<3)|(1<<2);
		PORTD&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
		
			 
		//CTC
		//prescaler 1024
		TCCR0A=0b00000010;
		TCCR0B=0b00000101;
		OCR0B=0b11111111;
		
		//TIMSK0|=0b00000100;
	}
	else if(configuration==2)	//PD6, PD7, PB0, PB1 timer0A
	{
		DDRD|=(1<<7)|(1<<6);
		DDRB|=(1<<1)|(1<<0);
		
		PORTD&=~((1<<7)|(1<<6));
		PORTB&=~((1<<1)|(1<<0));
		
		//CTC
		//prescaler 1024
		TCCR0A=0b00000010;
		TCCR0B=0b00000101;
		OCR0A=0b11111111;
		//TIMSK0|=0b00000010;
		
		
	}
	else if(configuration==3)	//PB2, PB3, PB4, PB5	timer2A
	{
		DDRB|=(1<<5)|(1<<4)|(1<<3)|(1<<2);
		
		PORTB&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
		
		//CTC
		//prescaler 1024
		TCCR2A=0b00000010;
		TCCR2B=0b00000111;
		OCR2A=0b11111111;
		
		//TIMSK2|=0b00000010;
	}
	else //PC0, PC1, PC2, PC3						timer2B
	{
		DDRC|=(1<<3)|(1<<2)|(1<<1)|(1<<0);
		
		PORTC&=~((1<<3)|(1<<2)|(1<<1)|(1<<0));
		
		//CTC
		//prescaler 1024
		TCCR2A=0b00000010;
		TCCR2B=0b00000111;
		OCR2B=0b11111111;
		
		//TIMSK2|=0b00000100;
	}
	steps=0;
	microstep=0;
	LOG("Init end, motor: ");
	LOG((int)(configuration));
	LOG("\n");
	sei();
	return true;
	
}
void StepperMotor_28BYJ48::changeDefaultDirection(bool direction)
{
	defaultDirection=direction;
	LOG("Motor");
	LOG((int)(configuration));
	if(direction)LOG(" Default direction is FORWARD\n");
	else LOG(" Default direction is BACKWARD\n");
}


void StepperMotor_28BYJ48::stop()
{
	switch(configuration)
	{
		case 1: TIMSK0&=~(1<<2);
				PORTD&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
				break;
		case 2: TIMSK0&=~(1<<1);
				PORTD&=~((1<<7)|(1<<6));
				PORTB&=~((1<<1)|(1<<0));
				break;
		case 3: TIMSK2&=~(1<<1);
				PORTB&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
				break;
		case 4: TIMSK2&=~(1<<2);
				PORTC&=~((1<<3)|(1<<2)|(1<<1)|(1<<0));
				break;
	}
	steps=0;
	microstep=0;
	LOG("Motor");
	LOG((int)(configuration));
	LOG(" stopped\n");
	
}


void StepperMotor_28BYJ48::microStep()
{
	
	if(steps==0)
	{
		stop();
	}
	if(defaultDirection == direction) microstep++;
	else microstep--;
	if(microstep>=8)
	{
		microstep=0;
		if(steps>0)steps--;
	}
	if(microstep<=-1) 
	{
		microstep=8;
		if(steps>0)steps--;
	}
	LOG("Motor");
	LOG((int)(configuration));
	LOG(" step ");
	LOG(steps);
	LOG(" microstep ");
	LOG((int)microstep);
	LOG("\n");
	
	if(configuration==1)	//PD2, PD3, PD4, PD5
	{
		PORTD&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
		
		switch(microstep)
		{
			case 0: PORTD|=(1<<2);
					break;
			case 1: PORTD|=(1<<3)|(1<<2);
					break;
			case 2: PORTD|=(1<<3);
					break;
			case 3: PORTD|=(1<<4)|(1<<3);
					break;
			case 4: PORTD|=(1<<4);
					break;
			case 5: PORTD|=(1<<5)|(1<<4);
					
					break;
			case 6: PORTD|=(1<<5);
					break;
			case 7: 
					PORTD|=(1<<5)|(1<<2);
					break;
		}
	}
	else if(configuration==2)	//PD6, PD7, PB0, PB1
	{
		PORTD&=~((1<<7)|(1<<6));
		PORTB&=~((1<<1)|(1<<0));
		
		switch(microstep)
		{
			case 0: PORTD|=(1<<6);
					break;
			case 1: PORTD|=(1<<7)|(1<<6);
					
					break;
			case 2: PORTD|=(1<<7);
					break;
			case 3: PORTD|=(1<<7);
					PORTB|=(1<<0);
					break;
			case 4: PORTB|=(1<<0);
					break;
			case 5: PORTB|=(1<<1)|(1<<0);
					
					break;
			case 6: PORTB|=(1<<1);
					break;
			case 7: PORTB|=(1<<1);
					PORTD|=(1<<6);
					break;
		}
	}
	else if(configuration==3)	//PB2, PB3, PB4, PB5
	{
		PORTB&=~((1<<5)|(1<<4)|(1<<3)|(1<<2));
		
		switch(microstep)
		{
			case 0: PORTB|=(1<<2);
					break;
			case 1: PORTB|=(1<<3)|(1<<2);
					break;
			case 2: PORTB|=(1<<3);
					break;
			case 3: PORTB|=(1<<4)|(1<<3);
					break;
			case 4: PORTB|=(1<<4);
					break;
			case 5: PORTB|=(1<<5)|(1<<4);
					break;
			case 6: PORTB|=(1<<5);
					break;
			case 7: PORTB|=(1<<5)|(1<<2);
					break;
		}
	}
	else			 //PC0, PC1, PC2, PC3
	{
		PORTC&=~((1<<3)|(1<<2)|(1<<1)|(1<<0));
		
		switch(microstep)
		{
			case 0: PORTC|=(1<<0);
					break;
			case 1: PORTC|=(1<<1)|(1<<0);
					break;
			case 2: PORTC|=(1<<1);
					break;
			case 3: PORTC|=(1<<2)|(1<<1);
					break;
			case 4: PORTC|=(1<<2);
					break;
			case 5: PORTC|=(1<<3)|(1<<2);
					break;
			case 6: PORTC|=(1<<3);
					break;
			case 7: PORTC|=(1<<3)|(1<<0);
					break;
		}
	}
	
	
}
void StepperMotor_28BYJ48::drive(unsigned char speed, bool direction)
{
	this->direction=direction;
	if(speed==0) 
	{
		stop();
		return;
	}
	if(speed>8) speed=8;
	unsigned char time=1<<(speed-1);
	
	LOG("Motor");
	LOG((int)(configuration));
	LOG(" speed ");
	LOG((int)speed);
	LOG("\n");
	switch(configuration)
	{
		case 1: TIMSK0|=1<<2;
				OCR0B=time;
				break;
		case 2: TIMSK0|=1<<1;
				OCR0A=time;
				break;
		case 3: TIMSK2|=1<<1;
				OCR2A=time;
				break;
		case 4: TIMSK2|=1<<2;
				OCR2B=time;
				break;
	}
	steps=-1;
	microstep=0;
}

void StepperMotor_28BYJ48::driveSteps(int steps, unsigned char speed, bool direction)
{
	drive(speed, direction);
	this->steps=steps;
}
StepperMotor_28BYJ48* StepperMotor_28BYJ48::getMotor(int num)
{
	return StepperMotor_28BYJ48::pActivatedConfiguration[num-1];
	
}

ISR(TIMER0_COMPB_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(1);
	if(motor!=NULL)motor->microStep();
}	
ISR(TIMER0_COMPA_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(2);
	if(motor!=NULL)motor->microStep();
}
ISR(TIMER2_COMPA_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(3);
	if(motor!=NULL)motor->microStep();
}
ISR(TIMER2_COMPB_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(4);
	if(motor!=NULL)motor->microStep();
}