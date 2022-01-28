// 
// 
// 

#include "Alarm.h"

Alarm::Alarm() {

}

bool Alarm::AlarmEmpty(int8_t pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

bool Alarm::AlarmLowBB(int8_t pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

void Alarm::AlarmBat(int8_t pin)
{
	digitalWrite(pin, 1);
	delay(250);
	digitalWrite(pin, 0);
}

void Alarm::BuzzerLow(int8_t pin)
{
	tone(pin, 4000, 500);
	delay(200);
	noTone(pin);
}

void Alarm::BuzzerBat(int8_t pin)
{
	tone(pin, 1500, 1000);
	delay(300);
	noTone(pin);
}
