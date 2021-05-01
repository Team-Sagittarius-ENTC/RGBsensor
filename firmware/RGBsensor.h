/*
  RGB Sensor Project
  ==================

  This is the header file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#ifndef RGBsensorFunctions
#define RGBsensorFunctions

#include <Arduino.h>

// this is the main class for the RGB sensor
class RGBsensor{
  private:
    byte Sensor[3]{}; // this is the RGB ldr pins
    byte color[3]{};
    byte ratio[3]{};
    byte LM[2][3]{};
    
  public:
    RGBsensor(byte tSensor[]); // this is the constructor for the sensor
    
    byte *readColor(bool calibrate = false); //this is the read colot method

    void calibrate();
    
    void displayColor(byte tcolor[]); // this function will display the color in the serial monitor
}; // end of the RGBsensor Class

#endif
