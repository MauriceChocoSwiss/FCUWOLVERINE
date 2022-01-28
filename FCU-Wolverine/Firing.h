#ifndef _FIRING_h
#define _FIRING_h
#include "arduino.h"

class Firing {
	public:
		Firing();
		void Fire(int8_t pin, int8_t dwel);
};

#endif
