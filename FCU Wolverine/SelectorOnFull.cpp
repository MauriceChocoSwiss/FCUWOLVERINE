#include <Arduino.h>
#include "SelectorOnFull.h"

SelectorOnFull::SelectorOnFull()
{
}

void SelectorOnFull::selectorFull(int pin, int dwel, int rof)
{
		digitalWrite(pin, 1);

		for (int x = 0; x < dwel; x++)
		{
			delay(1);
		}
		digitalWrite(pin, 0);	

		for (int z = 0; z <= 1000 / rof; z++)
		{
			delay(1);
		}	
}