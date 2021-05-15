#ifndef KEYPAD_FUNCTIONS
#define KEYPAD_FUNCTIONS

#include <Arduino.h>

class Keypad{
  private:
    byte key {};
    short keypad {};
    String inputString {"Bello"};

    void decode_();

  public:
    //constructor for the class
    Keypad(byte pin);
    String get_keys(byte length_ = 1);

  
}; //end of the keypad class



#endif
