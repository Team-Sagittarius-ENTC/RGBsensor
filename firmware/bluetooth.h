#ifndef BLUETOOTH_FUNCTIONS
#define BLUETOOTH_FUNCTIONS

class Bluetooth{
  private:
    byte EN = 4;
    byte STAT = 5;
    
  public:
    Bluetooth();
    bool isOn();
    String sendCommand(String Command);
};

#endif
