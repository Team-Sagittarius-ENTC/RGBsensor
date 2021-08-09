#ifndef KEYPAD_FUNCTIONS
#define KEYPAD_FUNCTIONS

#include <Arduino.h>

class Keypad{
	private:
	String keys[4][3] = { {"1", "2", "3"},
	{"4", "5", "6"},
	{"7", "8", "9"},
	{"*", "0", "#"}};
	short val = 0;
	
	public:
	Keypad();
	String read_key(bool halt = true);
};

#endif