#include "keypad.h"


Keypad::Keypad(){
	//set D4 - D7 output pins
	DDRD = DDRD | 0b11110000;
	// set PB3 - PB5 inputs
	DDRB = DDRB & 0b11000111;
}// end of keypad

String Keypad::read_key(bool halt){
	while (true){
		
		for(short i = 0; i < 4; ++i){
			PORTD = (PORTD & 0b00001111) | (1 << (i + 4)); //switching between 4 lines
			_delay_ms(1);
			
			val = ((0b00111000 & PINB) >> 3);
			if (val > 0){
				val = log(val) / log(2);
				//halt until release key
				while((0b00111000 & PINB) >> 3);

				PORTD = (PORTD & 0b00001111);
				return keys[i][val];
			}// end of if val > 0
			
		}//end of for loop

		if(!halt) break;
		
	}//end of while loop

	return "";
}// end of function