#include "keypad.h"

Keypad mykeypad = Keypad(A0); //creating the instance
void setup() {
  Serial.begin(9600);
}

void loop(){
  Serial.println(mykeypad.print_key(3));
}
