#include "Display.h"

Display lcd;

void startConversion(){
  ADCSRA |= 0b01000000; //set ADSC bit to one
}

void setup_ADC(byte pin){
  //setup the ADMUX register
  ADMUX = 0b01000000 | pin;

  //Setup Constrol status register of the ADC
    // ADC enable
    // ADC Interrupt enable
    // Prescallar to 128 th of system clock
  ADCSRA = 0b10001111;

  // Disable digital input budder
  DIDR0 = (1 << pin);

  startConversion();
}

ISR(ADC_vect){
  //startConversion();
  cli();
}

int analogRead_(byte pin){
  setup_ADC(pin);
  return ADC;
  sei();
}

void setup(){
}

void loop(){
  lcd.clear_();
  
  lcd.setCursor_(0,0);
  lcd.print_(String(analogRead_(0)));
  lcd.setCursor_(5,0);
  lcd.print_(String(analogRead_(1)));
  lcd.setCursor_(10,0);
  lcd.print_(String(analogRead_(2)));

//  lcd.setCursor_(0,1);
//  lcd.print_(String(analogRead(0)));
//  lcd.setCursor_(5,1);
//  lcd.print_(String(analogRead(1)));
//  lcd.setCursor_(10,1);
//  lcd.print_(String(analogRead(2)));

  delay(100);
}
