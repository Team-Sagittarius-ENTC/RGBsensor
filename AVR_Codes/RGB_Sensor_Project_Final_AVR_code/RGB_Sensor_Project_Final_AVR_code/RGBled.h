#ifndef rgbled_definition
#define rgbled_definition
#include <Arduino.h>

class RGBled
{

	private:
	void initRGB();
	void setDutyCycle(short dutyVal);
	
	
	public:
	RGBled();
	void lightLED(int color[]);
	void offLED();

};//end of RGBled class



#endif