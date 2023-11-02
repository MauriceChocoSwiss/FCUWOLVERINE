// 
// 
// 

#include "Alarm.h"

Alarm::Alarm() {

}

bool Alarm::AlarmEmpty(uint8_t pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

bool Alarm::AlarmLowBB(uint8_t pin)
{
	digitalWrite(pin, 1);
	delay(150);
	digitalWrite(pin, 0);

	return true;
}

void Alarm::AlarmBat(uint8_t pin)
{
	digitalWrite(pin, 1);
	delay(250);
	digitalWrite(pin, 0);
}

void Alarm::BuzzerLow(uint8_t pin)
{
	tone(pin, 4000, 500);
	delay(200);
	noTone(pin);
}

void Alarm::BuzzerBat(uint8_t pin)
{
	tone(pin, 1500, 1000);
	delay(300);
	noTone(pin);
}
