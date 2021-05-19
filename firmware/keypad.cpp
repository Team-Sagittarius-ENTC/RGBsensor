#include "keypad.h"

Keypad::Keypad(byte pin){
  key = pin; //Assigne private key to pin
}// end of the constructor

void Keypad::decode_(){
  if (keypad< 410 ){
    inputString +="3";
  }
  else if (keypad < 435){
    inputString +="6";
  }
  else if (keypad < 455){
    inputString +="9";
  }
  else if (keypad < 480){
    inputString +="#";
  }
  else if (keypad < 580){
    inputString +="2";
  }
  else if (keypad < 620){
    inputString +="5";
  }
  else if (keypad < 660){
    inputString +="8";
  }
  else if (keypad < 720){
    inputString +="0";
  }
  else if (keypad < 800){
    inputString +="1";
  }
  else if (keypad < 880){
    inputString +="4";
  }
  else if (keypad < 960){
    inputString +="7";
  }
  else {
    inputString +="*";
  }
}//end of the decode function

String Keypad::get_keys(byte length_ = 1){
  inputString = ""; // empty the input string
  while (inputString.length() < length_){

    keypad = analogRead(A3);
    delay(1);

    if (keypad > 0){
      decode_();
      // remember to ad a delay
      while (analogRead(key)>0){}
    }
  }// end of main while loop
  return inputString;
}// end of the gey keys function
