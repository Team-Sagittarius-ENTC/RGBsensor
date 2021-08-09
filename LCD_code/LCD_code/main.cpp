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
	PORTD = PORTD | 0b00001000;
	_delay_ms(1);
	PORTD = PORTD & 0b11110111;
} // end of the toggle enable 

void initLCD(){
	// E, RS
	PORTD = PORTD & 0b11110011;
		
	// initializing the display
		
	//display clear
	PORTD &= 0b00001111;
	PORTD |= 0b00000000;
	toggleEnable();
	
	//function set
	PORTD &= 0b00001111;
	PORTD |= 0b00100000;
	toggleEnable();
	
	//function set
	PORTD &= 0b00001111;
	PORTD |= 0b00100000;
	toggleEnable();
	PORTD &= 0b00001111;
	PORTD |= 0b10000000;
	toggleEnable();
	
	//display on of control
	PORTD &= 0b00001111;
	PORTD |= 0b00000000;
	toggleEnable();
	PORTD &= 0b00001111;
	PORTD |= 0b11110000;
	toggleEnable();
	
	
	//entry mode set
	PORTD &= 0b00001111;
	PORTD |= 0b00000000;
	toggleEnable();
	PORTD &= 0b00001111;
	PORTD |= 0b01100000;
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
	// E, RS
	PORTD = PORTD & 0b11110011;
	
	short temp = 0b10000000 | (x + 64*y);
	
	PORTD &= 0b00001111;
	PORTD = PORTD | (temp & 0b11110000);
	toggleEnable();
	
	PORTD &= 0b00001111;
	PORTD = PORTD | ((temp & 0b00001111) << 4);
	toggleEnable();
}

void clear(){
	// E, RS
	PORTD = PORTD & 0b11110011;
	
	
	//display clear
	PORTD &= 0b00001111;
	PORTD |= 0b00000000;
	toggleEnable();
	//display clear
	PORTD &= 0b00001111;
	PORTD |= 0b00000000;
	toggleEnable();
}

int main(void)
{
    
	//define the data direction
	DDRD = DDRD | 0b00111111; 
	
	initLCD(); // initializing the LCD display
	setCursor(2, 1);
	
	while(1){}
}// end of the main program

