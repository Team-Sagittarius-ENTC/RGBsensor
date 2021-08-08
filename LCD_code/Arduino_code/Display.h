#ifndef DisplayFunctions
#define DisplayFunctions

#include <Arduino.h>

class Display{
  
private:

  void toggleEnable();
  void initLCD();
  


  

public:
  Display(); // the constructor for the keypad

  // basic functions of the LCD
  void setCursor_(uint8_t x, uint8_t y);
  void clear_();

  void printMsg(String message, byte alignment, bool line); // function to printout messages
  void printMainMenu(); // function to print the main menu
  void printSensorMenu(); // function to print the sensor menu (SUB menu 1)
  void printRGBMenu(); // function to print the RGBled menu (SUB menu 2)

};


#endif
