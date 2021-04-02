/*
  Team Horizon

  Program Date    : 2nd April 2021
  Program version : 1.0.0
*/


// Define variables for LED handling
#define ledClk 2
#define ledPwm 10

// These are the global variables for functions
int color[3] = {134,32,200};
size_t i;

void setup(){
  // Set pinModes
  pinMode(ledClk, OUTPUT);
  pinMode(ledPwm, OUTPUT);
}// end of the void setup

void loop(){
  lightLed();
}// end of the void loop function


void setColor(){
  // this function will set the color for given color
  digitalWrite(ledPwm, LOW);
  //color setting proccess here
}

void lightLed(){
  // this function will set the color of the led to given color
  for (i=0; i<3; ++i){
    analogWrite(ledPwm, color[i]);
    pulse();
  }
}// end of the light led function

void pulse(){
  digitalWrite(ledClk, HIGH);
  digitalWrite(ledClk, LOW);
}// end of the pulsing function
