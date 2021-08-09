#ifndef rgbled_definition
#define rgbled_definition
#include <util/_delay_ms.h>

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