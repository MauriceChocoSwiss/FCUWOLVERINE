#include "SelectorOnFull.h"

SelectorOnFull::SelectorOnFull()
{

}

void SelectorOnFull::selectorFull(int pin, int dwel, int rof)
{
	digitalWrite(pin, 1);
	delay(dwel);
	digitalWrite(pin, 0);
	delay(rof);
}