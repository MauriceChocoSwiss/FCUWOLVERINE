#ifndef _FIRING_h
#define _FIRING_h
#include "arduino.h"

class Firing {
	public:
		Firing();
		void Fire(uint8_t pin, uint16_t dwel);
};

#endif
