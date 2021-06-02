
class Keypad
{
  private:

  public:
    Keypad()
    {
      //D4 D5 D6 D7 are outputs (already bcz display)
      DDRD |= 0b11110000;
      //B3 B4 B5 are inputs
      DDRB &= 0b11000111;
      PORTB |= 0b00100000;
    }
    
    char popKeyPress()
    {
      byte pressedRow;
      byte pressedCol;
      bool pressDetected=0;
      while(!pressDetected)
      {
        
        byte row=1;

        while(row<=4)
        {
          //powering the only selected row
          PORTD &= 0b00001111;
          PORTD |= (1<<(4+row-1));
          byte col=1;
          while(col<=3)
          {
            if(PINB & (1<<(3+col-1)))
              {
                pressDetected=1;
                pressedCol = col;
                pressedRow = row;
              }
              delay(4);
            col++;
          }//End:while for cols
          row++;
        }//End:while for rows
      }//End:While loop until pressDetect

      //at this point pressDetected
      char keyPositions[4][3] = {
                                {'1','2','3'},
                                {'4','5','6'},
                                {'7','8','9'},
                                {'*','0','#'}
                               };
      delay(200);//to stop multiple detection per one press
      return keyPositions[pressedRow-1][pressedCol-1];
    }//End:popKeyPress
    
};//End:Keypad class




void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);


//PORTD |= 0b11110000;
}//End:Setup

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.print(PINB,BIN);
  Serial.print("\n");
  delay(800);*/

  Keypad myKeypad;
  char m=myKeypad.popKeyPress();
  Serial.print(m);


   delay(400);//to stop multiple detection per one press
}//End : LOOP
