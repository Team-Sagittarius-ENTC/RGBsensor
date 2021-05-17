/*
  RGB Sensor Project
  ==================

  This is the header file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#ifndef DisplayFunctions
#define DisplayFunctions

#include <Arduino.h>


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Set the LCD address to 0x27 for a 16 column and 2 row display

LiquidCrystal_I2C  lcd(0x27, 16, 2);

void initLCD(){
  lcd,begin();
  lcd.backlight();
}

void printMsg(String message, int delay_ = 1000){
  lcd.clear();
  lcd.print(message);
  delay(delay_);
  lcd.clear();
}
