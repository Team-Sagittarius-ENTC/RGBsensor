#define ledClk 2
#define ledPwm 10

int color[3] = {134,32,200};
size_t i;

void setup(){
  pinMode(ledClk, OUTPUT);
  pinMode(ledPwm, OUTPUT);
  setColor();
}

void loop(){
  lightLed();
}


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
