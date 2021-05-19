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

class Display{
    private:
      LiquidCrystal lcd = LiquidCrystal(2,3,4,5,6,7);
      int  color[3]{};
      byte keypadPin;
      String tempInput = "";
      Keypad keypad = Keypad(A3);

      int inputColor();
      
    public:
      //define the constructor
      Display(byte pin);

      // Define public messages
      void printMsg(String message, byte alignment = 0, bool line = 0);
      int inputColor(byte positionx, byte positiony);

      // define menus
      void printMainMenu();
      void printSensorMenu();
      void printRGBMenu();
      int* colorInputDisplay();
};

#endif
