/*
 * RGB_Sensor_Project_Final_AVR_code.cpp
 *
 * Created: 8/9/2021 9:55:49 AM
 * Author : ASUS
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/_delay_ms.h>
#include <stdio.h>

#include "keypad.h"
#include "RGBsensor.h"
#include "Display.h"
#include "RGBled.h"

short ldrPins[3] = {2, 1, 0};
int *color {nullptr};

// creating instances of classes we defined
RGBsensor Sensor(ldrPins);
Keypad keypad;
RGBled Led;
Display Lcd;


int main(void)
{
	
	// Void setup code goes here

	//prting the welcome
	Lcd.printMsg("Welcome !!", 1, 0);
	Lcd.printMsg("Team Sagittarius", 1, 1);
	_delay_ms(500);
	

    /* Void loop code goes here */
    while (1) 
    {
		
		Lcd.printMainMenu();
		switch(keypad.read_key().toInt()){
			case 1:

			// we are at the sensoring part
			Lcd.printSensorMenu();
			switch(keypad.read_key().toInt()){
				case 1:
				// this is the point where we calibrate the sensor
				Sensor.calibrate(Lcd, keypad);
				break;

				case 2:
				Sensor.sensor(1);
				while(keypad.read_key(false) == ""){
					color = Sensor.readColor();
					Lcd.printLiveSense(color);
					_delay_ms(200);
				}
				Sensor.sensor(0);
				break;

				default:
				break;
			}//end of the sensor menu switching


			break;
			case 2:

			//we are at RGB ligtning part
			Lcd.printRGBMenu();
			switch(keypad.read_key().toInt()){
				case 1:
				color = Lcd.colorInputDisplay(keypad); // inputing the color from the keypad
				
				break;

				case 2:
				Sensor.sensor(1);
				while(keypad.read_key(false) == ""){
					color = Sensor.readColor();
					Lcd.printLiveSense(color);
					Sensor.displayColor(color);
					_delay_ms(20);
				}
				Sensor.sensor(0);
				break;

				default:
				break;
			}//end of the RGB menu switching

			break;

			default:
			// do not anything pass
			break;
		}
		
		
		
		
		
		
    }// end of the while true loop
}// end of the main

