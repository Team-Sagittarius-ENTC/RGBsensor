/*
  RGB Sensor Project
  ==================

  This is the Header file for the display liblary.
  Programmed By: Kajhanan Kailainathan 190286M
*/

#ifndef DisplayFunctions
#define DisplayFunctions

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "keypad.h"
#include "RGBled.h"

class Display{
    private:
      LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);
      int  color[3]{};
      byte keypadPin;
      String tempInput = "";
      byte ldrPins[3] = {A2, A1, A1};
      RGBled theLed;

      int inputColor();
      
    public:
      //define the constructor
      Display(byte pin);

      // Define public messages
      void printMsg(String message, byte alignment = 0, bool line = 0);
      int inputColor(byte positionx, byte positiony, Keypad keypad);

      // define menus
      void printMainMenu();
      void printSensorMenu();
      void printRGBMenu();
      void clear_();
      int* colorInputDisplay(Keypad keypad);
      void printLiveSense(int color_[]);
};

#endif
