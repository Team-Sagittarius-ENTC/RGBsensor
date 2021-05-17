#ifndef KEYPAD_FUNCTIONS
#define KEYPAD_FUNCTIONS

class Keypad{
  
private:
   byte key;
   short keypad;
   String inputString;
   void decode_();

public:
   //constructor for the keypad class
   Keypad(byte keypad_pin);  
   void print_key();
  
};  //end of the Keypad class


#endif
