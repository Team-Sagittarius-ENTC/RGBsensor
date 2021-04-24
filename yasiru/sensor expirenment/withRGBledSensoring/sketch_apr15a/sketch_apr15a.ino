#define pulsePin 2 // this is the pin for pulsing CD4017
#define readPin A0 // this is the pin for reading LDR value

const int LVALS[3]{62,62,54}; // these are the lower values for LDRs
const int HVALS[3]{545,600,360}; // these are the higher values for LDRs

const int DELAY{100}; // delay between shifting colors

unsigned short color[3]{}; // this will hold the color for us

unsigned int temp{}; // this is the temporary holder for readings




void pulse(){
  digitalWrite(pulsePin, HIGH);
  digitalWrite(pulsePin, LOW);
}// end of void pulse

void readColor(bool calibrate = false){
  for(size_t i = 0; i < 3; ++i){
    delay(10); // delay 20 millisoconds for turn on the led

    for(size_t j = 0; j < 10; ++j){
      if (calibrate)
        temp += analogRead(readPin); // read and add the values from the analog read
      else
        temp += map(analogRead(readPin), LVALS[i], HVALS[i], 10, 245); // read and add the values from the analog read
      delay(1); 
    }

    // now add the readed color for the color array
    color[i] = float(temp) / 10;
    temp = 0;

    pulse(); // change the color
  }// end of main for loop
}// end of void read color

void printData(){
  for(size_t i = 0; i < 3; ++i){
    Serial.print(color[i]);
    Serial.print(i == 2 ? "\n" : ",");
  }
}// end of void pintData

void setup(){
  Serial.begin(9600); // start the serial communication
  pinMode(pulsePin, OUTPUT); // set the pin mode for pulsing pin
}// end of void setup

void loop(){
  readColor(false);
  printData();

  delay(50);
}// end of void loop
