// VoltageCtrl.h

#ifndef _VOLTAGECTRL_h
#define _VOLTAGECTRL_h

#include "arduino.h"

class VoltageCtrl {
	public:
		VoltageCtrl();
		double VoltageValue(int pin, int voltConf);
		void alarmVoltage(int pin);
};

#endif

