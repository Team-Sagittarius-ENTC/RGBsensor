#include "Keypad.h"
#include <Arduino.h>

#include <Arduino.h>
Keypad::Keypad(byte keypad_pin){
  key = keypad_pin
} //end of the constructor keypad class

void Keypad::decode_(){
  if (keypad< 410 ){
    //lcd.print("3");
    inputString +="3";
  }
  else if (keypad < 435){
    //lcd.print("6");
    inputString +="6";
  }
  else if (keypad < 455){
    //lcd.print("9");
    inputString +="9";
  }
  else if (keypad < 480){
    //lcd.print("#");
    inputString +="#";
  }
  else if (keypad < 580){
    //lcd.print("2");
    inputString +="2";
  }
  else if (keypad < 620){
    //lcd.print("5");
    inputString +="5";
  }
  else if (keypad < 660){
    //lcd.print("8");
    inputString +="8";
  }
  else if (keypad < 720){
    //lcd.print("0");
    inputString +="0";
  }
  else if (keypad < 800){
    //lcd.print("1");
    inputString +="1";
  }
  else if (keypad < 880){
    //lcd.print("4");
    inputString +="4";
  }
  else if (keypad < 960){
    //lcd.print("7");
    inputString +="7";
  }
  else {
    //lcd.print("*");
    inputString +="*";
  }
}

void Keypad::print_key(short length_){
    while (inputString.length()<3 length_){
      keypad = analogRead(key);
      delay(200);
      if (keypad>0){
        decode_();
        delay(500);
        while (analogRead(key)>0){
        }
      }
    }
    return inoutString;
}//end of the printkey function
