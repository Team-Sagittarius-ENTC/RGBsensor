#include "keypad.h"
#include "RGBsensor.h"
#include "Display.h"
#include "RGBled.h"



byte ldrPins[3] = {A2, A1, A0};
int *color {nullptr};

// creating instances of classes we defined
RGBsensor Sensor(ldrPins);
Keypad keypad;
RGBled Led;
Display Lcd(A3);


void setup(){
  Serial.begin(9600);

  //prting the welcome
  Lcd.printMsg("Welcome !!", 1, 0);
  Lcd.printMsg("Team Sagittarius", 1, 1);
  delay(500);

  
}// end of the void setup function

void loop(){
  Lcd.printMainMenu();
  
  switch(keypad.read_key().toInt()){
    case 1:

      // we are at the sensoring part
      Lcd.printSensorMenu();
      switch(keypad.read_key().toInt()){
        case 1:
          // this is the point where we calibrate the sensor
          Lcd.printCallibrationMenu();
          switch(keypad.read_key().toInt()){
            case 1:
              Sensor.calibrate(Lcd, keypad, true);
            break;
            
            case 2:
              Sensor.calibrate(Lcd, keypad, false);
            break;
            
            default:
            break;
          }// end of the calibration switching
          
        break;

        case 2:
          Sensor.sensor(1);
          while(keypad.read_key(false) == ""){
            color = Sensor.readColor();
            Lcd.printLiveSense(color);
            Sensor.displayColor(color);
            delay(200);
          }
          Sensor.sensor(0);
        break;

        default:
        break;
      }//end of the sensor menu switching


    break;
    case 2:

      //we are at RGB ligtning part
      Lcd.printRGBMenu();
      switch(keypad.read_key().toInt()){
        case 1:
          color = Lcd.colorInputDisplay(keypad); // inputing the color from the keypad
          
        break;

        case 2:
          Sensor.sensor(1);
          while(keypad.read_key(false) == ""){
            color = Sensor.readColor();
            Lcd.printLiveSense(color);
            Sensor.displayColor(color);
            delay(20);
          }
          Sensor.sensor(0);
        break;

        default:
        break;
      }//end of the RGB menu switching

    break;

    default:
      // do not anything pass
    break;
  }
}// end of the void loop function
