#include "Display.h"
#include "keypad.h"
#include "RGBled.h"
#include <Arduino.h>
#include <LiquidCrystal.h>

Display::Display(byte pin){
  lcd.begin(16,2);
  lcd.clear();
  keypadPin = pin;
}// end of the Display contructor

void Display::clear_(){
  lcd.clear();
}

void Display::printMsg(String message, byte alignment = 0, bool line = 0){
  /*
    Left = 0
    Center = 1
    Right = 2
  */
  switch(alignment){
    case 0:
      lcd.setCursor(0,int(line));
    break;
    
    case 1:
      // Case 1 is for centering
      lcd.setCursor((16 - message.length()) / 2, int(line));
    break;

    case 2:
      //dosomething
    break;

    
  } // end of the switching
  lcd.print(message);
}// end of the print message function

void Display::printMainMenu(){
  lcd.clear();
  printMsg("Main Menu", 1, 0);
  printMsg("1:Sens 2:RgbLed", 0, 1);
}//end of the print main menu function

void Display::printSensorMenu(){
  lcd.clear();
  printMsg("Calibrate ?", 0, 0);
  printMsg("1:Yes    2:No", 0, 1);
}// end of the printSensorMenu() function

void Display::printRGBMenu(){
  lcd.clear();
  printMsg("1: Color input", 0, 0);
  printMsg("2: Real Time", 0, 1);
}// end of the printSensorMenu() function

int Display::inputColor(byte positionx, byte positiony){
  tempInput = ""; //clearing the tempInput
  String letter;

  while (true){
    letter = keypad.read_key(); 
    
    if(letter == "*"){
      // Accept the given value
      // Now we have to check for the errors
      if (tempInput.toInt() > 255){
        // clear the whole value
        lcd.setCursor(positionx, positiony);
        for(byte i = 0; i < tempInput.length(); ++i) lcd.print(" ");

        // print the error message
        lcd.setCursor(positionx, positiony);
        lcd.print("ERR");
        delay(500); // wait until user sees it
        
        lcd.setCursor(positionx, positiony); // going back again
        lcd.print("   ");

        lcd.setCursor(positionx, positiony);
        tempInput = "";
      }else{
        return tempInput.toInt();
      }   
    } // end of accept if statement
    
    else if(letter == "#" && tempInput.length()){
      // backspace the value
      tempInput = tempInput.substring(0, tempInput.length() - 1); // remove the last character from the tempInput
      lcd.setCursor(positionx + tempInput.length(), positiony); // going back one step
      lcd.print(" "); // clearing the character
      lcd.setCursor(positionx + tempInput.length(), positiony); // going back
    }// end of backspacing if else staement
    
    else{
      // get inputs and save it to tempInput
      tempInput += letter;
      lcd.print(letter);
    } // end of the last else
  }// end of the while loop
}// end of the input color function

int* Display::colorInputDisplay(){
  lcd.clear();
  lcd.print("R: ");
  lcd.blink();
  color[0] = inputColor(3, 0);

  lcd.setCursor(8, 0);
  lcd.print("G: ");
  lcd.blink();
  color[1] = inputColor(11, 0);

  lcd.setCursor(0, 1);
  lcd.print("B: ");
  lcd.blink();
  color[2] = inputColor(3, 1);
  lcd.noBlink();

  lcd.setCursor(8, 1);
  lcd.print("Done!");

  for(byte i = 0; i < 3; ++i){
    Serial.print(color[i]);
    Serial.print(i == 2 ? "\n" : ",");
  }

  while(keypad.read_key(false) == ""){
    theLed.lightLED(color);
  }
  lcd.clear();
  return color;
}

void Display::printLiveSense(int color_[]){

  lcd.clear();
  lcd.print("R: ");
  lcd.print(color_[0]);

  lcd.setCursor(8, 0);
  lcd.print("G: ");
  lcd.print(color_[1]);

  lcd.setCursor(0, 1);
  lcd.print("B: ");
  lcd.print(color_[2]);

  
}
