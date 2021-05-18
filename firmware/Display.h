/*
  RGB Sensor Project
  ==================

  This is the Header file for the display liblary.
  Programmed By: Kajhanan Kailainathan 190286M
*/

#ifndef DisplayFunctions
#define DisplayFunctions

#include <Arduino.h>

class Display{
  private:

  public:
    //constructor for the class
    Display();
    
    void printMsg(String message1, String message2 = "", int delay_ = 1000);

  
};

#endif
