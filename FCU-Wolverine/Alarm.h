// Alarm.h

#ifndef _ALARM_h
#define _ALARM_h
#include "arduino.h"

class Alarm {
public: 
	Alarm();
	bool AlarmEmpty(int8_t pin);
	bool AlarmLowBB(int8_t pin);
	void AlarmBat(int8_t pin);
	void BuzzerLow(int8_t pin);
	void BuzzerBat(int8_t pin);
};

#endif
