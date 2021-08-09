#include "RGBled.h"
#include <util/_delay_ms.h>
RGBled::RGBled()
{
	//setting B:0,1,2 to output
	DDRB |= ((1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2));

	// now initialize the timers and timer registers
	initRGB();
}
void RGBled::initRGB()
{
	// Set the mode of the timer 1 (16-bit) to 8-bit fast PWM
	// step 1 set WGM13, 12
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);
	
	// step 2 set WGM 11, 10
	TCCR1A |= (1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	
	// We need Non inverting PWM signal
	TCCR1A |= (1 << COM1B1);
	TCCR1A &= ~(1 << COM1B0);
	
	// We need 31KHz for the RGB switching
	// Therefore the pre-scaling is 1
	TCCR1B |= (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);
	
	// set the pinmode
	//DDRB |= (1 << PORTB2);//no need  defined before in constructor

	
}// end of the void initRGB

void RGBled::setDutyCycle(short dutyVal)
{

	
	// set the duty cycle
	OCR1B = dutyVal;
	
}//end of setDutyCycle


void RGBled::lightLED(int color[]){
	for (short i = 0; i < 3; ++i){
		PORTB = (PORTB & 0B11111100) | i;
		setDutyCycle(color[i]);
		_delay_ms(1);
	}//end  of switching loop
	
}// end of the function

void RGBled::offLED()
{
	setDutyCycle(0);
}//end of off led