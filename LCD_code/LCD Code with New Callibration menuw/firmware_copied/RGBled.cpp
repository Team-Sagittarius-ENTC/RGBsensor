#include "RGBled.h"
#include <Arduino.h>
RGBled::RGBled()
{
  initRGB();
}
void RGBled::initRGB()
  {
    pinMode(8, OUTPUT);

 
  }// end of the void initRGB

void RGBled::setDutyCycle(byte dutyVal)
{

    
}//end of setDutyCycle


void RGBled::lightLED(int color[]){
  digitalWrite(8,HIGH);

  if (color[0] < 32 && color[1] < 32 && color[2] < 32){
    digitalWrite(8,LOW);
  }
  analogWrite(5, color[0]);
  analogWrite(9, color[1]);
  analogWrite(10, color[2]);
  
}// end of the function

void RGBled::offLED()
{
  digitalWrite(8, LOW);
}//end of off led
