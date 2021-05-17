#include <LiquidCrystal.h>

int rs = 12;
int e = 11;
int d4 = 10;
int d5 = 9;
int d6 = 8;
int d7 = 7;

LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

int redLed=4;
int greenLed=3;
int blueLed=2;

String msgR="R?";
String msgG="G?";
String msgB="B?";
int R;
int G;
int B;

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
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

lcd.print(R);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
}
