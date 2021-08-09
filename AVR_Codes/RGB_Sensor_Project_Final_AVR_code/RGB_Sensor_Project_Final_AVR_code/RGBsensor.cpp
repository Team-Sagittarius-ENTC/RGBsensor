/*
  RGB Sensor Project
  ==================

  This is the cpp file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#include "RGBsensor.h"
#include "Display.h"
#include "keypad.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// Constructor for the sensor
RGBsensor::RGBsensor(short tSensor[]){
  /*
    This is the function for initialize the sensor. tSensor variable is an array passed by
    user when creating the instance. those are the RGB ldr pins.
  */
  // connect the sensor and initialize
  DDRC = DDRC | 0b00001000;
  for (short i = 0; i < 3; ++i) Sensor[i] = tSensor[i];
}// end of constructor

void RGBsensor::sensor(bool stat){
  if (stat) PORTC |= 0b00001000;
  else PORTC &= 0b11110111;
}// end of the sensor on of

float RGBsensor::minor(short i, short j){
  float arr[2][2] = {{0,0},{0,0}};
  
  short a = 0;
  short b = 0;
  for (short i_=0; i_<3; ++i_){
    if( i_ != i){
        b = 0;
        for (short j_=0; j_<3; ++j_){
          if(j_ != j){
            arr[a][b] = coeff_mat[i_][j_];
            b++;
          }// end of second if
        } // end of second for loop
        a++;
    }// end of main if
  }// end of the main for loop
  
  return (arr[0][0]*arr[1][1] - arr[0][1]*arr[1][0]) * (pow((-1), i) * pow((-1),j));
}// end of the minor function

void RGBsensor::update_coeff(short ref_){
  float beta = 0;
  float gamma = 0;
  float delta = 0;
  float theta = 0;

  for (short i = 0; i < 9; ++i){
    beta  += raw_data[i][ref_];
    gamma += pow(raw_data[i][ref_], 2);
    delta += pow(raw_data[i][ref_], 3);
    theta += pow(raw_data[i][ref_], 4);
  }// end of the for loop

  coeff_mat[0][0] = gamma;
  coeff_mat[0][1] = beta;
  coeff_mat[0][2] = 9;

  coeff_mat[1][0] = delta;
  coeff_mat[1][1] = gamma;
  coeff_mat[1][2] = beta;

  coeff_mat[2][0] = theta;
  coeff_mat[2][1] = delta;
  coeff_mat[2][2] = gamma;
}// end of the update coeff function


//Regression processor
void RGBsensor::procRegression(){
  float ans[3]{};
  float inv[3][3]{};
  float SIG_xy = 0;
  float SIG_xy2 = 0;
  float det;
  
  for (short m = 1; m < 4; ++m){
    
    SIG_xy = 0;
    SIG_xy2 = 0;

    for(short i = 0; i < 9; ++i){
        SIG_xy += raw_data[i][0]*raw_data[i][m];
        SIG_xy2 += raw_data[i][0]*pow(raw_data[i][m],2);
    }

    ans[0] = 1152; ans[1] = SIG_xy; ans[2] = SIG_xy2; /*Create the answer matrix*/
    update_coeff(m); /*Update coefficiant matrix*/

    /*Finding the inverse of the matrix*/
    det = coeff_mat[0][0] * minor(0,0) + coeff_mat[0][1] * minor(0,1) + coeff_mat[0][2] * minor(0,2);
    
    for(short i = 0; i < 3; ++i){
      for(short k = 0; k < 3; ++k){
          inv[i][k] = minor(k,i) / det;
      }    
    }

    /*Matrix multiplication and add to RGC matrix*/

    for(short i = 0; i < 3; ++i){
      for(short k = 0; k < 3; ++k){
        RGC[m-1][i] += (inv[i][k] * ans[k]);
      }
    }

  
  }// enf of the main for loop  
}//end of regressingpric

int RGBsensor::inverseRegression(int input, short ref){
  /*
    This is the function to do the reverse of procRegression function.
    This function will find the corresponting average value it came from using readed value
    The function will take the values in color variable and replace it with
    the result by inverse regression
  */
   int output = RGC[ref][0]*input*input*1E-4 + RGC[ref][1]*input*1E-2 + RGC[ref][2];

  if(output < 0) output = 0;
  else if(output > 255) output = 255;

  return output;

}//end of the inverse regression

void RGBsensor::startConversion(){
	ADCSRA |= 0b01000000; //set ADSC bit to one
}

void RGBsensor::setup_ADC(short pin){
	//setup the ADMUX register
	ADMUX = 0b01000000 | pin;

	//Setup Constrol status register of the ADC
	// ADC enable
	// ADC Interrupt enable
	// Prescallar to 128 th of system clock
	ADCSRA = 0b10001111;

	// Disable digital input budder
	DIDR0 = (1 << pin);

	startConversion();
}

ISR(ADC_vect){
	//startConversion();
	cli();
}

int RGBsensor::analogRead_(short pin){
	setup_ADC(pin);
	return ADC;
	sei();
}


// Sensor read color method
int *RGBsensor::readColor(bool calibrate){
  /*
    This is a public function.
    This function will read the color and do all processing and return final color to
    the user

    calibrate : set this to true if you want to get readings without any processing
              : set this to false if want with all processing
  */
	


  for(short i = 0; i < 3; ++i) color[i] = analogRead_(Sensor[i]);// reading the raw color

  if (calibrate){
    return color;
  }// end of calibration if statement
  
  else{
   //inverseRegression();
   for(short i = 0; i < 3; ++i) color[i] = inverseRegression(color[i], 2-i);// reading the raw color

   return color;
  }// end of if else statement
}//end of the read color function

// Sensor print color method
void RGBsensor::displayColor(int *tcolor){
  /*
    In various times we want to display the readed color.
    By calling this function we can show the values in color variable
  */
  
}// end of the displayColor method

// Sensor Calibration Method
void RGBsensor::calibrate(Display Lcd, Keypad keypad){

  /*ALGORITHM of the callibration process*/
  /*
      * Get 9 points from the printed table.
        * Trun on the sensor 
        * While (9 times)   
        *   Show the Requirenment in the LCD
        *   Capture the RGB values
        *   Save it in the raw data matrix
   
      * Use regression function to do regression
  */
  // Zero out the old RGC constants
  for(short i = 0; i < 3; ++i){
    for(short k = 0; k < 3; ++k){
      RGC[i][k] = 0;
    }
  }
    

  // reading data for the 9 shades of gray
  sensor(1); //turning on the sensor

  for(short i = 0; i < 9; ++i){
    
    Lcd.printMsg("Capture -> " + String(raw_data[i][0]));
    
    while (keypad.read_key(false) != "#"){
      readColor(true);
      Lcd.printMsg(String(color[0]) + ", " + String(color[1]) + ", " + String(color[2]), 0, true); // printing the color      
    }//Halt and don't read untill press the key
  
    readColor(true); // read the color

    for (short j = 1; j < 4; ++j){
      raw_data[i][4-j] = float(color[j-1]) / 100; //deviding the color and store it in the array
    }
    
  }// end of the for loop
  
  sensor(0); // turning off the sensor


  procRegression(); //Proccess the regression constants

  
}// end of calibration function