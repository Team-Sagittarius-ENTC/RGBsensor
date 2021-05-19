#include "RGBsensor.h"
#include "keypad.h"
#include "RGBled.h"

byte ldrPins[3] = {A2, A1, A0};
int *color {nullptr};

// creating instances of classes we defined
RGBsensor Sensor(ldrPins);
Keypad keypad(A3);
RGBled Led;


void setup(){
  Serial.begin(9600);
}// end of the void setup function

void loop(){
  



  
}// end of the void loop function
