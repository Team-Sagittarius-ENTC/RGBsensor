#include <LiquidCrystal.h>
#include "RGBsensor.h"
#include "keypad.h"

byte ldrPins[3] = {A2, A1, A0};
int *color {nullptr};

RGBsensor Sensor(ldrPins);
Keypad keypad(A3);
LiquidCrystal lcd(2,3,4,5,6,7);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
}// end of the void setup function

void loop(){
  



  
}// end of the void loop function
