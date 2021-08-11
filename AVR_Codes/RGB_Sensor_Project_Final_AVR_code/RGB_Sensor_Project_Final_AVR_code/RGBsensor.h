/*
  RGB Sensor Project
  ==================

  This is the header file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#ifndef RGBsensorFunctions
#define RGBsensorFunctions

#include <util/_delay_ms.h>
#include "Display.h"
#include "keypad.h"

// this is the main class for the RGB sensor
class RGBsensor{
  private:
    short Sensor[3]{}; // this is the RGB ldr pins
    int  color[3]{};  // this is the ptr array to process all the color data
    float coeff_mat[3][3] {}; // this is the coefficiant matrix which uses to calculate RGCs

    float raw_data[9][6]{
	    {0.00,   0.00,   0.00,   3.89, 2.43, 2.04},
	    {31.00,  31.00,  31.00,  4.53, 2.85, 2.59},
	    {63.00,  63.00,  63.00,  5.32, 3.49, 3.36},
	    {95.00,  95.00,  95.00,  6.25, 4.28, 4.28},
	    {127.00, 127.00, 127.00, 6.50, 4.60, 4.60},
	    {159.00, 159.00, 159.00, 6.96, 5.05, 5.07},
	    {191.00, 191.00, 191.00, 7.35, 5.51, 5.61},
	    {223.00, 223.00, 223.00, 7.95, 6.25, 6.35},
	    {255.00, 255.00, 255.00, 8.20, 6.60, 6.73}
    }; // this array will use the store sen sored data for the calibration purposes
    
    float RGC[3][3]{ //regression constants
	    {6.5529613039948345, -21.70716070508206, -10.88222916702216},
	    {1.4848949805768825, 46.67373805102034, -119.51068638392826},
	    {2.514421337210365, 31.627137726753972, -72.78155680513919 }
    };


    

    float minor(short i, short j); // this function is to find the minor matrixes (inverse matrix)

    void update_coeff(short ref_); // this function is to update the cofficiant matrix 
    
    void procRegression(); // this is the function to process the regression
    
    int inverseRegression(int input, short ref); // this is the function to invert the regression
    
  public:
    RGBsensor(short tSensor[]); // this is the constructor for the sensor
    
    int *readColor(bool calibrate = false); //this is the read colot method

    void calibrate(Display lcd, Keypad keypad); // this is the calibration function
    
    void displayColor(int *tcolor); // this function will display the color in the serial monitor

    void sensor(bool stat); // this function is used to control the sensor
	
	void startConversion();
	
	void setup_ADC(short pin);
	
	int analogRead_(short pin);

}; // end of the RGBsensor Class

#endif