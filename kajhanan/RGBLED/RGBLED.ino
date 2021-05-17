#include <LiquidCrystal.h> 

int redLed=4;
int greenLed=2;
int blueLed=3;

int rs = 7;
int e = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

String msgR="R?";
String msgG="G?";
String msgB="B?";
int R;
int G;
int B;

void setup(){
Serial.begin(9600);
pinMode(redLed,OUTPUT);
pinMode(greenLed,OUTPUT);
pinMode(blueLed,OUTPUT);
lcd.begin(16,2); 

Serial.println(msgR);
while (Serial.available()==0){}
R=Serial.parseInt();

Serial.println(msgG);
while (Serial.available()==1){}
G=Serial.parseInt();

Serial.println(msgB);
while (Serial.available()==1){}
B=Serial.parseInt();
}

void loop() {
lcd.setCursor(0,0);
lcd.print("Hello World");

analogWrite(redLed,R);
analogWrite(greenLed,G);
analogWrite(blueLed,B);
}
  
