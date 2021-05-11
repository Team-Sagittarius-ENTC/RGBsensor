 #include "RGBsensor.h"

byte ldrPins[3] = {A2, A1, A0};
int *color {nullptr};

RGBsensor Sensor(ldrPins);

void setup(){
  Serial.begin(9600);
  //Sensor.doSomething();
  //Sensor.calibrate();
}// end of the void setup function

void loop(){
  color = Sensor.readColor();
  Sensor.displayColor(color);
}// end of the void loop function
