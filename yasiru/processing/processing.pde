  
import processing.serial.*;

Serial myPort;  // The serial port
String data;
int index1,  R, G, B;


void setup() {
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
  size(1500, 800);
  background(30);
  
  delay(1000);
}

void draw() {
   background(R, G, B);
}

void serialEvent (Serial myPort) { // starts reading data from the Serial Port
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  
  if (data != null){
    data = data.substring(0, data.length()-1);
    
    index1 = data.indexOf(',');
    R = int(data.substring(0, index1));
    
    data = data.substring(index1 + 1, data.length());
    index1 = data.indexOf(',');
    G = int(data.substring(0, index1));
    
    data = data.substring(index1 + 1, data.length());
    B = int(data.substring(0, index1));
   
    
  }
}
