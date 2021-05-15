int key=A0;
int keypad;
char let;
int red_led_pin= 11;
int green_led_pin= 10;
int blue_led_pin= 9;
String inputString;
long inputInt;
int val[3];
int int_val;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);  


void setup() {
  pinMode(red_led_pin,OUTPUT);
  pinMode(green_led_pin,OUTPUT);
  pinMode(blue_led_pin,OUTPUT);
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  inputString.reserve(3); 
  lcd.setCursor(5,0);
  lcd.print("WELCOME");
  delay(2000);
  lcd.clear();

}
void decode_(){
  let="";
  if (keypad< 410 ){
    lcd.print("3");
    inputString +="3";
  }
  else if (keypad < 435){
    lcd.print("6");
    inputString +="6";
  }
  else if (keypad < 455){
    lcd.print("9");
    inputString +="9";
  }
  else if (keypad < 480){
    lcd.print("#");
    inputString +="#";
  }
  else if (keypad < 580){
    lcd.print("2");
    inputString +="2";
  }
  else if (keypad < 620){
    lcd.print("5");
    inputString +="5";
  }
  else if (keypad < 660){
    lcd.print("8");
    inputString +="8";
  }
  else if (keypad < 720){
    lcd.print("0");
    inputString +="0";
  }
  else if (keypad < 800){
    lcd.print("1");
    inputString +="1";
  }
  else if (keypad < 880){
    lcd.print("4");
    inputString +="4";
  }
  else if (keypad < 960){
    lcd.print("7");
    inputString +="7";
  }
  else {
    lcd.print("*");
    inputString +="*";
  }
}

void print_key(){
    while (inputString.length()<3){
      keypad = analogRead(key);
      delay(200);
      if (keypad>0){
        decode_();
        delay(500);
        while (analogRead(key)>0){
        }
      }
    }
    int_val = inputString.toInt();
    delay(500);
    lcd.clear();
}
void loop() {
  lcd.setCursor(0,0);
  lcd.print("Enter 3 digit");
  lcd.setCursor(0,1);
  lcd.print("for RGB values");
  delay(3000);
  lcd.clear();
  
  inputString="";
  lcd.setCursor(0,0);
  lcd.print("ENTER R VALUE");
  lcd.setCursor(0,1);
  print_key();
  val[0]=int_val;
  delay(500);
  inputString="";
  lcd.setCursor(0,0);
  lcd.print("ENTER G VALUE");
  lcd.setCursor(0,1);
  print_key();
  val[1]=int_val;

  inputString="";
  lcd.setCursor(0,0);
  lcd.print("ENTER B VALUE");
  lcd.setCursor(0,1);
  print_key();
  val[2]=int_val;

  if ((val[0]<=255) && (val[1]<=255) && (val[2]<=255)){
    analogWrite(red_led_pin,val[0]);
    analogWrite(green_led_pin,val[1]);
    analogWrite(blue_led_pin,val[2]);
    lcd.clear();
  }
}
