#include "Display.h"
#include "keypad.h"
#include "RGBled.h"
#include <Arduino.h>

Display::Display(){
  //define the data direction
  DDRD = DDRD | 0b00111111; 
  initLCD(); // initializing the LCD display
}// end of the initializing

void Display::toggleEnable(){
  //toggling Enable
  PORTD = PORTD | 0b00001000;
  delay(1);
  PORTD = PORTD & 0b11110111;
} // end of the toggle enabl

void Display::initLCD(){
  // E, RS
  PORTD = PORTD & 0b11110011;
    
  // initializing the display
    
  //display clear
  PORTD &= 0b00001111;
  PORTD |= 0b00000000;
  toggleEnable();
  
  //function set
  PORTD &= 0b00001111;
  PORTD |= 0b00100000;
  toggleEnable();
  
  //function set
  PORTD &= 0b00001111;
  PORTD |= 0b00100000;
  toggleEnable();
  PORTD &= 0b00001111;
  PORTD |= 0b10000000;
  toggleEnable();
  
  //display on of control
  PORTD &= 0b00001111;
  PORTD |= 0b00000000;
  toggleEnable();
  PORTD &= 0b00001111;
  PORTD |= 0b11000000;
  toggleEnable();
  
  
  //entry mode set
  PORTD &= 0b00001111;
  PORTD |= 0b00000000;
  toggleEnable();
  PORTD &= 0b00001111;
  PORTD |= 0b01100000;
  toggleEnable();
  
}// end of init Display function

void Display::setCursor_(uint8_t x, uint8_t y){
  // E, RS
  PORTD = PORTD & 0b11110011;
  
  short temp = 0b10000000 | (x + 64*y);
  
  PORTD &= 0b00001111;
  PORTD = PORTD | (temp & 0b11110000);
  toggleEnable();
  
  PORTD &= 0b00001111;
  PORTD = PORTD | ((temp & 0b00001111) << 4);
  toggleEnable();
}// end of the setcursor_ function

void Display::clear_(){
  // E, RS
  PORTD = PORTD & 0b11110011;
  
  
  //display clear
  PORTD &= 0b00001111;
  PORTD |= 0b00000000;
  toggleEnable();
  //display clear
  PORTD &= 0b00001111;
  PORTD |= 0b00010000;
  toggleEnable();
}// end of the clear function

void Display::print_(String message){
  // LCD Printing method

  /*Set register select to 1 and Enable pin to 0*/
  PORTD = PORTD & 0b11110011;
  PORTD = PORTD | 0b00000100;


  char charArr[30] {}; // empty array
  message.toCharArray(charArr, message.length()+1); //converting message to an array
  
  for (byte i = 0; i < message.length(); ++i){

    PORTD &= 0b00001111; //clearing out needed space
    PORTD = PORTD | (charArr[i] & 0b11110000); // send first 4 bits
    toggleEnable();
    
    PORTD &= 0b00001111;
    PORTD = PORTD | ((charArr[i] & 0b00001111) << 4); // send 2nd 4 bits
    toggleEnable();
    
  }// end of the for loop

}// end of the print function

void Display::blink_(bool status_){
  if (status_){
    //display on of control
    PORTD &= 0b00001111;
    PORTD |= 0b00000000;
    toggleEnable();
    PORTD &= 0b00001111;
    PORTD |= 0b11110000;
    toggleEnable();
  } // end of the if true statement

  else{
    //display on of control
    PORTD &= 0b00001111;
    PORTD |= 0b00000000;
    toggleEnable();
    PORTD &= 0b00001111;
    PORTD |= 0b11000000;
    toggleEnable();
  }
}// end of the blink_ function

void Display::printMsg(String message, byte alignment, bool line){
  /*
    Left = 0
    Center = 1
    Right = 2
  */
  switch(alignment){
    case 0:
      setCursor_(0,int(line));
    break;
    
    case 1:
      // Case 1 is for centering
      setCursor_((16 - message.length()) / 2, int(line));
    break;

    case 2:
      //dosomething
    break;

    
  } // end of the switching


  print_(message);
  
}// end of the print Msg function

void Display::printMainMenu(){
  clear_();
  printMsg("Main Menu", 1, 0);
  printMsg("1:Sens 2:RgbLed", 0, 1);
}

void Display::printSensorMenu(){
  clear_();
  printMsg("Calibrate ?", 0, 0);
  printMsg("1:Yes    2:No", 0, 1);
}

void Display::printRGBMenu(){
  clear_();
  printMsg("1: Color input", 0, 0);
  printMsg("2: Real Time", 0, 1);
}

int Display::inputColor(byte positionx, byte positiony, Keypad keypad){
  tempInput = ""; //clearing the tempInput
  String letter;

  while (true){
    letter = keypad.read_key(); 
    
    if(letter == "*"){
      // Accept the given value
      // Now we have to check for the errors
      if (tempInput.toInt() > 255){
        // clear the whole value
        setCursor_(positionx, positiony);
        for(byte i = 0; i < tempInput.length(); ++i) print_(" ");

        // print the error message
        setCursor_(positionx, positiony);
        print_("ERR");
        delay(500); // wait until user sees it
        
        setCursor_(positionx, positiony); // going back again
        print_("   ");

        setCursor_(positionx, positiony);
        tempInput = "";
      }else{
        return tempInput.toInt();
      }   
    } // end of accept if statement
    
    else if(letter == "#" && tempInput.length()){
      // backspace the value
      tempInput = tempInput.substring(0, tempInput.length() - 1); // remove the last character from the tempInput
      setCursor_(positionx + tempInput.length(), positiony); // going back one step
      print_(" "); // clearing the character
      setCursor_(positionx + tempInput.length(), positiony); // going back
    }// end of backspacing if else staement
    
    else{
      // get inputs and save it to tempInput
      tempInput += letter;
      print_(letter);
    } // end of the last else
  }// end of the while loop
  
}// end of the input COlor functiono

int* Display::colorInputDisplay(Keypad keypad){
  clear_();
  blink_(true);

  setCursor_(0, 0);
  print_("R: ");
  color[0] = inputColor(3, 0, keypad);

  setCursor_(8, 0);
  print_("G: ");
  color[1] = inputColor(11, 0, keypad);

  setCursor_(0, 1);
  print_("B: ");
  color[2] = inputColor(3, 1, keypad);
  
  blink_(false);

  setCursor_(8, 1);
  print_("Done!");

  for(byte i = 0; i < 3; ++i){
    Serial.print(color[i]);
    Serial.print(i == 2 ? "\r\n" : ",");
  }

  while(keypad.read_key(false) == ""){
    theLed.lightLED(color);
  }
  clear_();
  return color;
} // end of the display input color function

void Display::printLiveSense(int color_[]){
  clear_();
  print_("R: ");
  print_(String(color_[2]));

  setCursor_(8, 0);
  print_("G: ");
  print_(String(color_[1]));

  setCursor_(0, 1);
  print_("B: ");
  print_(String(color_[0]));
} // end of the function printLive Sense
