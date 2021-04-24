#include <LiquidCrystal.h>

// define the lcd
LiquidCrystal lcd(2,3,4,5,6,7);

// these variables are or the sensor reading process
const int ldrPins[3] = {A0, A1, A2};
short color[3] = {};
double ratio[3] = {1,1,1};

// these values are only for testing
short LM[2][3] = {{}, {1023, 1023, 1023}};

void readColor(bool calibrate = false){
  // declaring a variable to get the average
  short holder[3] = {};

  // read and add all values to get the average
  // since we are using 2 ms delay it will take nearly 20 ms to read the color
  for(size_t i = 0; i < 10; ++i){
    for(size_t j = 0; j < 3; ++j)
      holder[j] += analogRead(ldrPins[j]);
      delay(2);
  }// end of the for loop

  // now get the average
  for (size_t i = 0; i < 3; ++i){
    if (calibrate){
      color[i] = holder[i] / 10 * ratio[i];
    }else{
      color[i] = (holder[i] / 10) * ratio[i];
      color[i] = int(map(color[i], LM[0][i], LM[1][i], 10, 245));
    }
  }   
}// end of the read color function

void calibrate(){
  readColor(true); // read the RGB values
  double average = {};
  for (size_t i = 0; i < 3; ++i) average += (float(color[i])/3);
  for (size_t i = 0; i < 3; ++i) ratio[i] = average / color[i];

  // then assign that value to minimum of LM
  readColor(true);
  for (short i = 0; i < 3; ++i)
    LM[0][i] = color[i];
  
}// end of calibration

void sendBT(){
  Serial.print(color[0]);
  Serial.print(",");
  Serial.print(color[1]);
  Serial.print(",");
  Serial.print(color[2]);
  Serial.println();
}// end of printing details in to the serial monitor and Blutooth

void sendLCD(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("R:");
  lcd.setCursor(3,0);
  lcd.print(color[0]);

  lcd.setCursor(8,0);
  lcd.print("G:");
  lcd.setCursor(11,0);
  lcd.print(color[1]);
  
  lcd.setCursor(0,1);
  lcd.print("B:");
  lcd.setCursor(3,1);
  lcd.print(color[2]);

}// end of printing details in to the serial monitor and Blutooth

void setup(){
  lcd.begin(16,2); // for the lcd screen
  delay(200); // wait to start lcd
  Serial.begin(9600); // for the serial monitor and Blutooth
  while(!Serial){} // wait for starting serial
  calibrate(); // calibrate sensors
}// end of void seup

void loop(){
  readColor(); // read the color from the sensor
  sendBT(); // output data using blutooth
  sendLCD(); // output data using LCD screen
}// end of void loop
