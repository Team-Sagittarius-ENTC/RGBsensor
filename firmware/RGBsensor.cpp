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
  // connect the sensor and initialize
  for (byte i = 0; i < 3; ++i) Sensor[i] = tSensor[i];
}// end of constructor

//Regression processor
void RGBsensor::procRegression(int16_t avg){
  // set color to calculated regressions
  // red = RGC[0][0] * pow(avg + RGC[0][1], RGC[0][2]) + RCONSTS[0]
  for(byte i = 0; i < 3; ++i)color[i] = RGC[i][0] * pow(avg + RGC[i][1], RGC[i][2]) + RCONSTS[i];
}//end of regressingpric

void RGBsensor::inverseRegression(){
  for (byte i = 0; i < 3; ++i){
    color[i] = pow( (double(color[i]) - RCONSTS[i]) / RGC[i][0], 1 / RGC[i][2] ) - RGC[i][1];
  }
}//end of the inverse regression

// Sensor read color method
int *RGBsensor::readColor(bool calibrate = false){
  float ratio[3] {1, 1.13517, 1.19640};
  for(byte i = 0; i < 3; ++i) color[i] = analogRead(Sensor[i]) * ratio[i]; // reading the raw color

  if (calibrate){
    return color;
  }// end of calibration if statement
  
  else{
   //regression here
   inverseRegression();
   //mapout the colort
   
   for(byte i = 0; i < 3; ++i){
      color[i] = map(color[i], 300, 890, 5, 250);
      if(color[i] >= 255) color[i] = 255;
      else if (color[i] <= 0) color[i] = 0;
   } 
   
   
   return color;
  }// end of if else statement
}//end of the read color function

// Sensor print color method
void RGBsensor::displayColor(int *tcolor){
  for(byte i = 0; i < 3; ++i) {
    Serial.print(tcolor[i]);
    Serial.print(i == 2 ? "\n" : ",");
  }
}// end of the displayColor method

void RGBsensor::doSomething(){
  procRegression(400);
  displayColor(color);
  inverseRegression();
  displayColor(color);
  calibrate();
  procRegression(400);
  inverseRegression();
  displayColor(color);
  
}

// Sensor Calibration Method
void RGBsensor::calibrate(){
  /*First of all get all */
  
  #define SAMPLING_SPACE 10 // this will be the sampling space
  int16_t samples[50][4]{}; // this array will contain the samples of the ldr

  // now it is time to fill up the array
  for(byte i = 0; i < 50; ++i){
    if(i == 0){
      readColor(true); //read the color 
      memcpy(samples[0], color, sizeof(color)); //copy color to the samples
      samples[0][3] = float(color[0] + color[1] + color[2]) / 3;
    } //if this loop running for the first time
    else{

      while (true){
        readColor(true); // read the color
        // take the average of the color
        int16_t average = float(color[0] + color[1] + color[2]) / 3;
        
        if (abs(samples[i-1][3] - average) >= SAMPLING_SPACE){
          memcpy(samples[i], color, sizeof(color)); //copy color to the samples
          samples[i][3] = average;
          break;  
        }
      }//end of while loop
    }//end of else


    
    Serial.print("Calibration Percentage -> ");
    Serial.print(2 * i);
    Serial.println("%");
  }//end of filling for loop

  for(byte i = 0; i < 50; ++i){
  Serial.print("[");
  for(byte j = 0; j < 4; ++j){
    Serial.print(samples[i][j]);
    Serial.print(j == 3 ? "" : ", ");
  }
  Serial.println("],");
  }
  

  // OK now we have to find the corect regression constants
  // memset(RCONSTS, NULL, sizeof(RCONSTS)); //zero out the predefined verical constants
  
  for(byte i = 0; i < 50; ++i){
    procRegression(samples[i][3]); //do regression now calculated values are in the color variable
    // get differences and append change samples to the difference
    for(byte j = 0; j < 3; ++j) samples[i][j] -= color[j];

    //set the temp sum
    for(byte j = 0; j < 3; ++j) {
      if(i != 0) samples[0][j] += samples[i][j]; 
    }
  }// end of for loop

  Serial.println("\n\n------------------------------------------\n\n");

  for(byte i = 0; i < 50; ++i){
  Serial.print("[");
  for(byte j = 0; j < 4; ++j){
    Serial.print(samples[i][j]);
    Serial.print(j == 3 ? "" : ", ");
  }
  Serial.println("],");
  }

  //correct the regression constant
  for(byte i = 0; i < 3; ++i) RCONSTS[i] += double(samples[0][i]) / 3;

  
  

}// end of calibration function
