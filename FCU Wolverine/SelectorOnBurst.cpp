// 
// 
// 

#include "SelectorOnBurst.h"

SelectorOnBurst::SelectorOnBurst()
{

}

bool SelectorOnBurst::selectorBurst(int pin, int dwel, int rof, int repeat)
{
	for (int x = 0; x <= repeat; x++) {
		digitalWrite(pin, 1);
		delay(dwel);
		digitalWrite(pin, 0);
		delay(1000/rof);
	}

	return true;
}