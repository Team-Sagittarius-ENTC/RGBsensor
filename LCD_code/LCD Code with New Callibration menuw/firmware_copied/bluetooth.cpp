#include <Arduino.h>
#include "bluetooth.h"

Bluetooth::Bluetooth(){
  DDRC |= (DDRC << EN);
  DDRC &= ~(DDRC << STAT);
}// end of the constructor

bool Bluetooth::isOn(){
  if(analogRead(A5) > 100){
    return true;
  }else{
    return false;
  }
}

String Bluetooth::sendCommand(String Command){
  PORTC |= (PORTC << EN);

  if(Serial){
    Serial.flush();
    delay(2);
    Serial.end();
    delay(500);
  }

  Serial.begin(34200);

  Serial.print(Command);
  delay(500);
  String result = "";

  for(byte i = 0; i < 100; ++i){
    while(Serial.available() > 0){
      result += Serial.read();
    }
  }

  Serial.flush();
  delay(2);
  Serial.end();
  delay(500);

  Serial.begin(9600);
  
  PORTC &= ~(PORTC << EN);

  return result;
}
