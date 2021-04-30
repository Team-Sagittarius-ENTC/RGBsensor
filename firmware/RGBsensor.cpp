/*
  RGB Sensor Project
  ==================

  This is the cpp file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#include "RGBsensor.h"
#include <Arduino.h>

Sensor::Sensor(double *tratio, short **tLM){
  for(short i = 0; i < 3; ++i) ratio[i] = tratio[i];

  for(short i = 0; i < 2; ++i){
    for (short j = 0; i < 3; ++i){
      LM[i][j] = tLM[i][j];
    }
  } 
} // end of the Sensor calss constructor


int *Sensor::readColor(bool calibrate = false){
  // declaring a variable to get the average
  float holder[3] {};
  int finalColor[3] {};

  // read and add all values to get the average
  // since we are using 2 ms delay it will take nearly 20 ms to read the color
  for(short i = 0; i < 10; ++i){
    for(short j = 0; j < 3; ++j){
        holder[j] += analogRead(ldrPins[j]);
        delay(2);
    }
  }// end of the for loop

  // now get the average
  for (short i = 0; i < 3; ++i){
    if (calibrate){
      finalColor[i] = holder[i] / 10 * ratio[i];
    }else{
      finalColor[i] = (holder[i] / 10) * ratio[i];
      finalColor[i] = int(map(finalColor[i], LM[0][i], LM[1][i], 10, 245));
    }
  }// end of getting the average

  return finalColor; //returning the color of the readed paper 
}// end of Sensor::readColor function


void Sensor::calibrate(){
  int *color = readColor(true); // read the RGB values
  double average = {};
  for (short i = 0; i < 3; ++i) average += (float(color[i])/3);
  for (short i = 0; i < 3; ++i) ratio[i] = average / color[i];

  // then assign that value to minimum of LM
  readColor(true);
  for (short i = 0; i < 3; ++i)
    LM[0][i] = color[i];
}// end of Sensor::calibrate function