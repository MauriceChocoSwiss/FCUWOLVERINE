// Alarm.h

#ifndef _ALARM_h
#define _ALARM_h
#include "arduino.h"

class Alarm {
public: 
	Alarm();
	bool AlarmEmpty(int pin);
	bool AlarmLowBB(int pin);
	void AlarmBat(int pin);
	void BuzzerLow(int pin);
	void BuzzerBat(int pin);
};

#endif

