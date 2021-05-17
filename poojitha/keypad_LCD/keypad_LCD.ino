#include <Keypad.h>
#include <LiquidCrystal.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns
int red_led_pin= 11;
int green_led_pin= 10;
int blue_led_pin= 9;


char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {4,3,2,1};   //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {7,6,5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);   // Pin Assign
String inputString;
long inputInt;
int val[3];
void setup() {
  pinMode(red_led_pin,OUTPUT);
  pinMode(green_led_pin,OUTPUT);
  pinMode(blue_led_pin,OUTPUT);
  lcd.begin(16,2);
  inputString.reserve(3); // maximum number of digit for a number is 10, change if needed
  lcd.setCursor(5,0);
  lcd.print("WELCOME");
  delay(2000);
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
  while (inputString.length()<3){
    char key = keypad.waitForKey();
    lcd.print(key);
    inputString +=key;
  }
  delay(500);
  lcd.clear();
  val[0]=inputString.toInt();
  inputString="";
  lcd.setCursor(0,0);
  lcd.print("ENTER G VALUE");
  lcd.setCursor(0,1);
  while (inputString.length()<3){
    char key = keypad.waitForKey();
    lcd.print(key);
    inputString +=key;
  }
  delay(500);
  lcd.clear();
  val[1]=inputString.toInt();
  inputString="";
  lcd.setCursor(0,0);
  lcd.print("ENTER B VALUE");
  lcd.setCursor(0,1);
  while (inputString.length()<3){
    char key = keypad.waitForKey();
    lcd.print(key);
    inputString +=key;
  }
  delay(500);
  lcd.clear();
  val[2]=inputString.toInt();
  if ((val[0]<=255) && (val[1]<=255) && (val[2]<=255)){
    analogWrite(red_led_pin,val[0]);
    analogWrite(green_led_pin,val[1]);
    analogWrite(blue_led_pin,val[2]);
    lcd.clear();
    delay(100);
    lcd.print("PRESS ANY KEY");
    lcd.setCursor(0,1);
    lcd.print("FOR NEXT COLOUR:");
    char next=keypad.waitForKey();
    lcd.print(next);
    delay(1000);
    lcd.clear();
  }
}
