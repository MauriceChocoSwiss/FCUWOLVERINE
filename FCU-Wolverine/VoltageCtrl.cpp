#include "VoltageCtrl.h"

/** Mesure la r�f�rence interne � 1.1 volts */
unsigned int analogReadReference(void) {

	/* Elimine toutes charges r�siduelles */
	ADMUX = 0x4F;
	delayMicroseconds(5);

	/* S�lectionne la r�f�rence interne � 1.1 volts comme point de mesure, avec comme limite haute VCC */
	ADMUX = 0x4E;
	delayMicroseconds(200);

	/* Active le convertisseur analogique -> num�rique */
	ADCSRA |= (1 << ADEN);

	/* Lance une conversion analogique -> num�rique */
	ADCSRA |= (1 << ADSC);

	/* Attend la fin de la conversion */
	while (ADCSRA & (1 << ADSC));

	/* R�cup�re le r�sultat de la conversion */
	return ADCL | (ADCH << 8);
}

VoltageCtrl::VoltageCtrl() {

}

double VoltageCtrl::VoltageValue(int pin) {
	float real_vin = (((analogRead(pin) * 1.1)/ analogReadReference()) * 4) -0.20;
	
	return real_vin;
}

bool VoltageCtrl::alarmVoltage(int pin)
{
	if (VoltageValue(pin) < 7.40)
	{
		return true;
	}

	return false;
}
