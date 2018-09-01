// 
// 
// 

#include "Alarm.h"

Alarm::Alarm() {

}

bool Alarm::AlarmEmpty(int pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

bool Alarm::AlarmLowBB(int pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

void Alarm::AlarmBat(int pin)
{

}