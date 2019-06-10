#include "28BYJ48.h"


StepperMotor_28BYJ48* StepperMotor_28BYJ48::pActivatedConfiguration[4]={0};

StepperMotor_28BYJ48::StepperMotor_28BYJ48(char configuration)
{
	
	this->configuration=configuration;
}
bool StepperMotor_28BYJ48::init()
{
	if(configuration<0 || configuration>3) return false;
	if(pActivatedConfiguration[configuration-1]!=NULL) return false;
	
	pActivatedConfiguration[configuration-1]=this;
	
	if(configuration==1)	//PD1, PD0, PD4, PC6   timer1A
	{
		DDRD|=(1<<4)|(1<<1)|(1<<0);
		DDRC|=(1<<6);
		
		PORTD&=~((1<<4)|(1<<1)|(1<<0));
		PORTC&=~(1<<6);
			 
		//CTC
		//prescaler 1024
		TCCR1A=0b00000000;
		TCCR1B=0b00011101;
		OCR1AH=0b00000001;
		OCR1AL=0b00000000;
		ICR1H=0b00000000;
		ICR1L=0b11111111;
		TIMSK1|=0b00000100;
	}
	else if(configuration==2)	//PD7, PE6, PB4, PB5	timer3A
	{
		DDRD|=(1<<7);
		DDRE|=(1<<6);
		DDRB|=(1<<5)|(1<<4);
		
		PORTD&=~(1<<7);
		PORTE&=~(1<<6);
		PORTB&=~((1<<4)|(1<<5));
		
		//CTC
		//prescaler 1024
		TCCR3A=0b00000000;
		TCCR3B=0b00011101;
		OCR3AH=0b00000001;
		OCR3AL=0b00000000;
		ICR3H=0b00000000;
		ICR3L=0b11111111;
		TIMSK3|=0b00000100;
		
		
	}
	else if(configuration==3)	//PB6, PB2, PB3, PB1	timer3B
	{
		DDRB|=(1<<6)|(1<<3)|(1<<2)|(1<<1);
		
		PORTB&=~((1<<6)|(1<<3)|(1<<2)|(1<<1));
		
		//CTC
		//prescaler 1024
		TCCR3A=0b00000000;
		TCCR3B=0b00011101;
		OCR3BH=0b00000001;
		OCR3BL=0b00000000;
		ICR3H=0b00000000;
		ICR3L=0b11111111;
		TIMSK3|=0b00000010;
	}
	else //PF7, PF6, PF5, PF4						timer1B
	{
		DDRF|=(1<<7)|(1<<6)|(1<<5)|(1<<4);
		
		PORTF&=~((1<<7)|(1<<6)|(1<<5)|(1<<4));
		
		//CTC
		//prescaler 1024
		TCCR1A=0b00000000;
		TCCR1B=0b00011101;
		OCR1BH=0b00000001;
		OCR1BL=0b00000000;
		ICR1H=0b00000000;
		ICR1L=0b11111111;
		TIMSK1|=0b00000010;
	}
	steps=0;
	microstep=0;
	
	sei();
	return true;
	
}
void StepperMotor_28BYJ48::changeDefaultDirection(bool direction)
{
	defaultDirection=direction;
}


void StepperMotor_28BYJ48::stop()
{
	switch(configuration)
	{
		case 1: OCR1AH=0b00000001;
				PORTD&=~((1<<4)|(1<<1)|(1<<0));
				PORTC&=~(1<<6);
				break;
		case 2: OCR3AH=0b00000001;
				PORTD&=~(1<<7);
				PORTE&=~(1<<6);
				PORTB&=~((1<<4)|(1<<5));
				break;
		case 3: OCR3BH=0b00000001;
				PORTB&=~((1<<6)|(1<<3)|(1<<2)|(1<<1));
				break;
		case 4: OCR1BH=0b00000001;
				PORTF&=~((1<<7)|(1<<6)|(1<<5)|(1<<4));
				break;
	}
	steps=0;
	microstep=0;
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
	
	
	if(configuration==1)
	{
		PORTD&=~((1<<4)|(1<<1)|(1<<0));
		PORTC&=~(1<<6);
		
		switch(microstep)
		{
			case 0: PORTD|=(1<<1);
					break;
			case 1: PORTD|=(1<<1)|(1<<0);
					break;
			case 2: PORTD|=(1<<0);
					break;
			case 3: PORTD|=(1<<4)|(1<<0);
					break;
			case 4: PORTD|=(1<<4);
					break;
			case 5: PORTD|=(1<<4);
					PORTC|=(1<<6);
					break;
			case 6: PORTC|=(1<<6);
					break;
			case 7: PORTC|=(1<<6);
					PORTD|=(1<<1);
					break;
		}
	}
	else if(configuration==2)
	{
		PORTD&=~(1<<7);
		PORTE&=~(1<<6);
		PORTB&=~((1<<4)|(1<<5));
		
		switch(microstep)
		{
			case 0: PORTD|=(1<<7);
					break;
			case 1: PORTD|=(1<<7);
					PORTE|=(1<<6);
					break;
			case 2: PORTE|=(1<<6);
					break;
			case 3: PORTE|=(1<<6);
					PORTB|=(1<<4);
					break;
			case 4: PORTB|=(1<<4);
					break;
			case 5: PORTB|=(1<<4)|(1<<5);
					
					break;
			case 6: PORTB|=(1<<5);
					break;
			case 7: PORTB|=(1<<5);
					PORTD|=(1<<7);
					break;
		}
	}
	else if(configuration==3)
	{
		PORTB&=~((1<<6)|(1<<3)|(1<<2)|(1<<1));
		
		switch(microstep)
		{
			case 0: PORTB|=(1<<6);
					break;
			case 1: PORTB|=(1<<6)|(1<<2);
					break;
			case 2: PORTB|=(1<<2);
					break;
			case 3: PORTB|=(1<<2)|(1<<3);
					break;
			case 4: PORTB|=(1<<3);
					break;
			case 5: PORTB|=(1<<3)|(1<<1);
					break;
			case 6: PORTB|=(1<<1);
					break;
			case 7: PORTB|=(1<<1)|(1<<6);
					break;
		}
	}
	else
	{
		PORTF&=~((1<<7)|(1<<6)|(1<<5)|(1<<4));
		
		switch(microstep)
		{
			case 0: PORTF|=(1<<7);
					break;
			case 1: PORTF|=(1<<7)|(1<<6);
					break;
			case 2: PORTF|=(1<<6);
					break;
			case 3: PORTF|=(1<<6)|(1<<5);
					break;
			case 4: PORTF|=(1<<5);
					break;
			case 5: PORTF|=(1<<5)|(1<<4);
					break;
			case 6: PORTF|=(1<<4);
					break;
			case 7: PORTF|=(1<<7)|(1<<4);
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
	switch(configuration)
	{
		case 1: OCR1AH=0;
				OCR1AL=time;
				break;
		case 2: OCR3AH=0;
				OCR3AL=time;
				break;
		case 3: OCR3BH=0;
				OCR3BL=time;
				break;
		case 4: OCR1BH=0;
				OCR1BL=time;
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

ISR(TIMER1_COMPA_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(1);
	if(motor!=NULL)motor->microStep();
}	
ISR(TIMER3_COMPA_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(2);
	if(motor!=NULL)motor->microStep();
}
ISR(TIMER3_COMPB_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(3);
	if(motor!=NULL)motor->microStep();
}
ISR(TIMER1_COMPB_vect)
{
	StepperMotor_28BYJ48*  motor=StepperMotor_28BYJ48::getMotor(4);
	if(motor!=NULL)motor->microStep();
}