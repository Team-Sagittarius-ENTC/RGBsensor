/*
  RGB Sensor Project
  ==================

  This is the cpp file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#include "RGBsensor.h"
#include <Arduino.h>

// Constructor for the sensor
RGBsensor::RGBsensor(byte tSensor[]){
  for (byte i = 0; i < 3; ++i) Sensor[i] = tSensor[i];
}

// Sensor read color method
byte *RGBsensor::readColor(bool calibrate = false){
  short tempColor[3] = {}; // this array will hold temorary data for processing
  for(byte i = 0; i < 3; ++i) tempColor[i] = analogRead(Sensor[i]); // reading the raw color

  for(byte i = 0; i < 3; ++i) {
    Serial.print(tempColor[i]);
    Serial.print(i == 2 ? "\n" : ", ");
  }
  
  // process the color here
  
  
  
  return color;
}//end of the read color function

// Sensor print color method
void RGBsensor::displayColor(byte tcolor[]){
  for(byte i = 0; i < 3; ++i) {
    Serial.print(tcolor[i]);
    Serial.print(i == 2 ? "\n" : ", ");
  }
}// end of the displayColor method

// Sensor Calibration Method
void RGBsensor::calibrate(){
  
}
