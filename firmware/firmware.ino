#include "RGBsensor.h"

short LM[2][3] = {{}, {577,564,645}};
double ratio[3] = {2.33, 6.78, 9.23};
byte ldrPins[3] = {A2, A1, A0};
byte *color {nullptr};

RGBsensor Sensor(ldrPins);

void setup(){
  Serial.begin(9600);
}// end of the void setup function

void loop(){
  color = Sensor.readColor();
  //Sensor.displayColor(color);
}// end of the void loop function
