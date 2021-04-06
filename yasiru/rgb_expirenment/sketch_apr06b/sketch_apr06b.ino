
#include <LiquidCrystal.h>

LiquidCrystal lcd (2, 3, 4, 5, 6, 7);

const int ldrPins[3] = {A0, A1, A2};
int color[3] = {};

void setup(){
  lcd.begin(16, 2);
  for (size_t i = 0; i < 3; ++i) pinMode(ldrPins[i], INPUT);
}// end of void seup

void loop(){
  for (size_t i = 0; i < 3; ++i) color[i] = analogRead(ldrPins[i]);

  printlcd();

  delay(1000);

  
}// end of void loop

void printlcd(){
  lcd.clear();
  for (size_t i = 0; i < 3; ++i){
    lcd.setCursor(4*i, 0);
    lcd.print(color[i]);
  }
}
