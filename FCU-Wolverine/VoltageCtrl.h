// VoltageCtrl.h

#ifndef _VOLTAGECTRL_h
#define _VOLTAGECTRL_h

#include "arduino.h"

class VoltageCtrl {
	public:
		VoltageCtrl();
		double VoltageValue(uint8_t pin);
		bool alarmVoltage(uint8_t pin, unsigned long currentMillis);
};

#endif
