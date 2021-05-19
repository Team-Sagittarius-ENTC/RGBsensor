#include "RGBsensor.h"
#include "keypad.h"
#include "RGBled.h"
#include "Display.h"



byte ldrPins[3] = {A2, A1, A0};
int *color {nullptr};

// creating instances of classes we defined
RGBsensor Sensor(ldrPins);
Keypad keypad(A3);
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

  switch(keypad.get_keys().toInt()){
    case 1:

      // we are at the sensoring part
      Lcd.printSensorMenu();
      switch(keypad.get_keys().toInt()){
        case 1:
          Lcd.printMsg("||At calibration");
          while(1);
        break;

        case 2:
          Lcd.printMsg("||At N Calibration");
          while(1);
        break;

        default:
        break;
      }//end of the sensor menu switching


    break;
    case 2:

      //we are at RGB ligtning part
      Lcd.printRGBMenu();
      switch(keypad.get_keys().toInt()){
        case 1:
          color = Lcd.colorInputDisplay(); // inputing the color from the keypad
          
        break;

        case 2:
          Lcd.printMsg("||Real Time");
          while(1);
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
