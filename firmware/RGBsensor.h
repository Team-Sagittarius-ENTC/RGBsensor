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
    int  color[3]{};  // this is the ptr array to process all the color data
    
    const double PROGMEM RGC[3][3]{ //regression constants
      { 3714.2750367674116   , 281.9907034616211   , 0.1}, // for red
      { 0.013065432118179211 , 1335.9090733992175  , 1.5}, // for green
      { 0.3260776975740072   , -188.96905355531214 , 1.2} // for blue
    };
    double RCONSTS[3] = { -6626.2939872758525 , -486.6226029668186 , 56.54299632875735 }; // vertical adjustment

    
    void procRegression(int16_t avg);
    void inverseRegression();
    
  public:
    RGBsensor(byte tSensor[]); // this is the constructor for the sensor
    
    int *readColor(bool calibrate = false); //this is the read colot method

    void calibrate(bool compare = false); // this is the calibration function
    
    void displayColor(int *tcolor); // this function will display the color in the serial monitor

}; // end of the RGBsensor Class

#endif
