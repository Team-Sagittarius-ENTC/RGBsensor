/*
 * LCD_code.cpp
 *
 * Created: 5/16/2021 8:23:47 PM
 * Author : ASUS
 */ 

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>


void toggleEnable(){
	//toggling Enable
	PORTC = PORTC | 0b00000100;
	_delay_ms(1);
	PORTC = PORTC & 0b11111011;
}

void initLCD(){
	// E, RW, RS
	PORTC = PORTC & 0b11111000;
		
	// initializing the display
		
	//display clear
	PORTB = 0b00000001;
	toggleEnable();
	//function set
	PORTB = 0b00111000;
	toggleEnable();
	//display on of control
	PORTB = 0b00001111;
	toggleEnable();
	//entry mode set
	PORTB = 0b00000110;
	toggleEnable();
	
}

void print(const char Message[], uint8_t size_){
	//writing data
	PORTC &= 0b11111000;
	PORTC |= 0b00000001; //register select 1
	
	for(uint8_t i = 0; i < size_; ++i ){
		PORTB = Message[i];
		toggleEnable();
	}
}

void setCursor(uint8_t x, uint8_t y){
	PORTC &= 0b11111000;
	PORTB = 0b10000000 | (x + 64*y);
	toggleEnable();
}

void clear(){
	PORTC &= 0b11111000;
	PORTB = 0b00000001;
	toggleEnable();
}

int main(void)
{
    
	//define the data direction
	DDRB = 0b11111111;
	DDRC |= 0b00000111;
	
	
	
	
	// initializing the display
	initLCD();
	
	setCursor(2, 0);
	print("Hello There", 6);
	
	_delay_ms(2000);
	clear();
	
	setCursor(0, 1);
	print("Good Bye");
	
	
	while(1){}
}// end of the main program

