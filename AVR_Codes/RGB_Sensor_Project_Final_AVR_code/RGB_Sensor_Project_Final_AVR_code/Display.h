#ifndef DisplayFunctions
#define DisplayFunctions

#include <Arduino.h>
#include "keypad.h"
#include "RGBled.h"

class Display{
	
	private:

	//Defining private variables
	String tempInput = "";
	int  color[3]{};
	RGBled theLed;

	void toggleEnable();
	void initLCD();
	


	

	public:
	Display(); // the constructor for the keypad

	// basic functions of the LCD
	void setCursor_(uint8_t x, uint8_t y);
	void clear_();
	void print_(String message);
	void blink_(bool status_);

	void printMsg(String message, short alignment = 0, bool line = 0); // function to printout messages
	void printMainMenu(); // function to print the main menu
	void printSensorMenu(); // function to print the sensor menu (SUB menu 1)
	void printRGBMenu(); // function to print the RGBled menu (SUB menu 2)

	int inputColor(short positionx, short positiony, Keypad keypad); // this function is used to input color when needed

	int* colorInputDisplay(Keypad keypad); // this function prints nice interface for reading the color from the keypad

	void printLiveSense(int color_[]); // this function shows live sensed color

};


#endif