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
	digitalWrite(pin, 1);
	delay(250);
	digitalWrite(pin, 0);
}

void Alarm::BuzzerLow(int pin)
{
	tone(pin, 4000, 500);
	delay(200);
	noTone(pin);
}

void Alarm::BuzzerBat(int pin);
{
	tone(buzzer, 2000, 1000);
	delay(300);
	noTone(buzzer);
}