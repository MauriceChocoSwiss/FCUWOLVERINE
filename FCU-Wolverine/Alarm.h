// Alarm.h

#ifndef _ALARM_h
#define _ALARM_h
#include "arduino.h"

class Alarm {
public: 
	Alarm();
	bool AlarmEmpty(uint8_t pin);
	bool AlarmLowBB(uint8_t pin);
	void AlarmBat(uint8_t pin);
	void BuzzerLow(uint8_t pin);
	void BuzzerBat(uint8_t pin);
};

#endif
