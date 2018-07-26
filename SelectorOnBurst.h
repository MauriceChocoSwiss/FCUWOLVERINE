// SelectorOnBurst.h

#ifndef _SELECTORONBURST_h
#define _SELECTORONBURST_h

#include "arduino.h"

class SelectorOnBurst{
	public:
		SelectorOnBurst();
		bool selectorBurst(int pin, int dwel, int rof, int repeat);
};

#endif

