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
	delay(dwel);
	digitalWrite(pin, 0);
}