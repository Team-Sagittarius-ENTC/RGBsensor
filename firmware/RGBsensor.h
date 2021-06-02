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
      { 636001.0376489708 , 165409.19316159718 , 0.1}, // for red
      { 0.0307475033803342 , 83.38789385867578 , 1.5}, // for green
      { 0.036533711170305024 , 850560.6621504327 , 1.2}, // for blue
    };
    double RCONSTS[3] = { -2115106.925056781 , 52.7447217477211 , -476682.09714456595 }; // vertical adjustment
    

    
    void procRegression(int16_t avg);
    void inverseRegression();
    //void sensor(bool stat);
    
  public:
    void sensor(bool stat);
    RGBsensor(byte tSensor[]); // this is the constructor for the sensor
    
    int *readColor(bool calibrate = false); //this is the read colot method

    void calibrate(Display lcd, bool compare = false); // this is the calibration function
    
    void displayColor(int *tcolor); // this function will display the color in the serial monitor

}; // end of the RGBsensor Class

#endif
