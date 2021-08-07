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

// this is the main class for the RGB sensor
class RGBsensor{
  private:
    byte Sensor[3]{}; // this is the RGB ldr pins
    int  color[3]{};  // this is the ptr array to process all the color data
    
    const double PROGMEM RGC[3][3]{ //regression constants
      {0.0007179, -0.298761, 4.15205},
      {0.0003251, 0.282137, -110.862},
      {0.0002248, 0.339544, -86.8318}
    };
    

    
    void procRegression(int16_t avg);
    int inverseRegression(int input, byte ref);
    //void sensor(bool stat);
    
  public:
    void sensor(bool stat);
    RGBsensor(byte tSensor[]); // this is the constructor for the sensor
    
    int *readColor(bool calibrate = false); //this is the read colot method

    void calibrate(Display lcd, bool compare = false); // this is the calibration function
    
    void displayColor(int *tcolor); // this function will display the color in the serial monitor

}; // end of the RGBsensor Class

#endif
