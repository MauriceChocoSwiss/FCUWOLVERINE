#include "VoltageCtrl.h"

/** Mesure la référence interne à 1.1 volts */
unsigned int analogReadReference(void) {

	/* Elimine toutes charges résiduelles */
	ADMUX = 0x4F;
	delayMicroseconds(5);

	/* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
	ADMUX = 0x4E;
	delayMicroseconds(200);

	/* Active le convertisseur analogique -> numérique */
	ADCSRA |= (1 << ADEN);

	/* Lance une conversion analogique -> numérique */
	ADCSRA |= (1 << ADSC);

	/* Attend la fin de la conversion */
	while (ADCSRA & (1 << ADSC));

	/* Récupère le résultat de la conversion */
	return ADCL | (ADCH << 8);
}

VoltageCtrl::VoltageCtrl() {

}

double VoltageCtrl::VoltageValue(int pin) {
	float real_vin = ((analogRead(pin) * 1.1)/ analogReadReference()) * 4;
	
	return real_vin;
}

bool VoltageCtrl::alarmVoltage(int pin)
{
	if (VoltageValue(pin) < 7.20)
	{
		return true;
	}

	return false;
}