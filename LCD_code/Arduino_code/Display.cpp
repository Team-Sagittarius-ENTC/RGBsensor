#include "Display.h"

Display::Display(){
  //define the data direction
  DDRD = DDRD | 0b00111111; 
  initLCD(); // initializing the LCD display
}// end of the initializing

void Display::toggleEnable(){
  //toggling Enable
  PORTD = PORTD | 0b00001000;
  _delay_ms(1);
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
  PORTD |= 0b11110000;
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
  PORTD |= 0b00000000;
  toggleEnable();
}// end of the clear function

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
