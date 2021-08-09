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
  void print_(String message);
  void blink_(bool status_);

};


#endif
