// 
// 
// 
#include <Arduino.h>
#include "SelectorOnBurst.h"

SelectorOnBurst::SelectorOnBurst()
{
}

bool SelectorOnBurst::selectorBurst(int pin, int dwel, int rof, int repeat)
{
	for (int x = 0; x <= repeat; x++) {

		digitalWrite(pin, 1);

		for (int x = 0; x <= dwel; x++)
		{
			delay(1);
		}
		digitalWrite(pin, 0);

		for (int z = 0; z <= 1000 / rof; z++)
		{
			delay(1);
		}
	}

	return true;
}