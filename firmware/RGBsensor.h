/*
  RGB Sensor Project
  ==================

  This is the header file for RGB sensor liblary.
  Programmed By: Yasiru Senerath karunanayaka 190301H
*/

#ifndef RGBsensor
#define RGBsensor

class Sensor{
  private:
    const int ldrPins[3] {};
    double ratio[3] {};
    short LM[2][3] {};
    
  public:
    int * readColor(bool calibrate);
    void calibrate();

    // This is the constructor for the class
    Sensor(double *tratio, short **tLM);
};// end of the Sensor class

#endif
