/*
  RGB Sensor Project
  ==================

  This is the cpp file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#include "RGBsensor.h"
#include <Arduino.h>
#include "Display.h"

// Constructor for the sensor
RGBsensor::RGBsensor(byte tSensor[]){
  /*
    This is the function for initialize the sensor. tSensor variable is an array passed by
    user when creating the instance. those are the RGB ldr pins.
  */
  // connect the sensor and initialize
  DDRC = DDRC | 0b00001000;
  for (byte i = 0; i < 3; ++i) Sensor[i] = tSensor[i];
}// end of constructor

void RGBsensor::sensor(bool stat){
  if (stat) PORTC |= 0b00001000;
  else PORTC &= 0b11110111;
}// end of the sensor on of

//Regression processor
void RGBsensor::procRegression(int16_t avg){
  /*
    This function will take global regression constants.
    Will return calculated RGB values for given average value
    This function will used to find optimized regression constants
  */
  // set color to calculated regressions
  for(byte i = 0; i < 3; ++i)color[i] = RGC[i][0] * pow(avg + RGC[i][1], RGC[i][2]) + RCONSTS[i];
}//end of regressingpric

void RGBsensor::inverseRegression(){
  /*
    This is the function to do the reverse of procRegression function.
    This function will find the corresponting average value it came from using readed value
    The function will take the values in color variable and replace it with
    the result by inverse regression
  */
  
  for (byte i = 0; i < 3; ++i){
    color[i] = pow( (double(color[i]) - RCONSTS[i]) / RGC[i][0], 1 / RGC[i][2] ) - RGC[i][1];
  }
}//end of the inverse regression

// Sensor read color method
int *RGBsensor::readColor(bool calibrate = false){
  /*
    This is a public function.
    This function will read the color and do all processing and return final color to
    the user

    calibrate : set this to true if you want to get readings without any processing
              : set this to false if want with all processing
  */

  // to increase the sensiviry of green and blue increase multiply it with a scalar
  float ratio[3] {1, 0.9285, 0.6316};
  for(byte i = 0; i < 3; ++i) color[i] = analogRead(Sensor[i]) * ratio[i]; // reading the raw color

  if (calibrate){
    return color;
  }// end of calibration if statement
  
  else{
   //regression here
   //inverseRegression();
   //mapout the colort
   int mins[3] = {197,222,252};
   int maxs[3] = {704, 634, 533};
   for(byte i = 0; i < 3; ++i){
      color[i] = map(color[i], mins[i], maxs[i], 5, 250);
      if(color[i] >= 255) color[i] = 255;
      else if (color[i] <= 0) color[i] = 0;
   } 
   
   
   return color;
  }// end of if else statement
}//end of the read color function

// Sensor print color method
void RGBsensor::displayColor(int *tcolor){
  /*
    In various times we want to display the readed color.
    By calling this function we can show the values in color variable
  */
  Serial.println(String(tcolor[2]) + "," + String(tcolor[1]) + "," + String(tcolor[0]));
  
}// end of the displayColor method

// Sensor Calibration Method
void RGBsensor::calibrate(Display Lcd, bool compare = false){
  sensor(1); //turning on the sensor
  /*
    * This is the main function in reading process
    * This function will do some processing and find optimised vertical RCONST for equation
    * We can read color without calibrating too. Because we have already found the constants.
    * this function will only optimize those for the environment
    * compare: set this to true if you want regression process data
  */
  
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
      // since we need to reject near values and get other we need infintie loop
      // and breck it if we got a reading
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


    Lcd.clear_();
    Lcd.printMsg("Percentage >", 0, 0);
    Lcd.printMsg(String(2 * i) + " %", 0, 1);
    //Serial.print("Calibration Percentage -> ");
    //Serial.print(2 * i);
    //Serial.println("%");
  }//end of filling for loop

  if(compare){
    for(byte i = 0; i < 50; ++i){
      Serial.print("[");
      for(byte j = 0; j < 4; ++j){
        Serial.print(samples[i][j]);
        Serial.print(j == 3 ? "" : ", ");
      }
      Serial.println("],");
    }
  }// end of if
  
  

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


  if(compare){
    Serial.println("\n\n------------------------------------------\n\n");
    for(byte i = 0; i < 50; ++i){
      Serial.print("[");
      for(byte j = 0; j < 4; ++j){
        Serial.print(samples[i][j]);
        Serial.print(j == 3 ? "" : ", ");
      }
      Serial.println("],");
    }
  }// end of if
  

  //correct the regression constant
  for(byte i = 0; i < 3; ++i) RCONSTS[i] += double(samples[0][i]) / 3;

  sensor(0); // turning of the sensor
}// end of calibration function
