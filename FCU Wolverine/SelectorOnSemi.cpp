// 
// 
// 

#include <Arduino.h>
#include "SelectorOnSemi.h"

SelectorOnSemi::SelectorOnSemi() {
}

void SelectorOnSemi::selectorSemi(int pin, int dwel)
{
	digitalWrite(pin, 1);

	for (int x = 0; x < dwel; x++)
	{	
		delay(1);
	}
	digitalWrite(pin, 0);	
}