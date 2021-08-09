/*
  RGB Sensor Project
  ==================

  This is the header file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#ifndef RGBsensorFunctions
#define RGBsensorFunctions

#include <Arduino.h>
#include "Display.h"
#include "keypad.h"

// this is the main class for the RGB sensor
class RGBsensor{
  private:
    short Sensor[3]{}; // this is the RGB ldr pins
    int  color[3]{};  // this is the ptr array to process all the color data
    float coeff_mat[3][3] {}; // this is the coefficiant matrix which uses to calculate RGCs

    float raw_data[9][4]{
       {0   , 0,0,0},
       {31  , 0,0,0},
       {63  , 0,0,0},
       {95  , 0,0,0},
       {127 , 0,0,0},
       {159 , 0,0,0},
       {191 , 0,0,0},
       {223 , 0,0,0},
       {255 , 0,0,0}                      
    }; // this array will use the store sensored data for the callibration purposes
    
    float RGC[3][3]{ //regression constants
      {7.179, -29.8761, 4.15205},
      {3.251, 28.2137, -110.862},
      {2.248, 33.9544, -86.8318}
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