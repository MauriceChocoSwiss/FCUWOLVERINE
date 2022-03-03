#include "Alarm.h"
#include "Menu.h"
#include "VoltageCtrl.h"
#include "Firing.h"
#include <EEPROM.h>

//pin assignment
int trigger = 2;
int8_t selector = 3;
int8_t charger = 4;
int8_t reloadLEDRed = 7;
int8_t reloadLEDGreen = 6;
int8_t reloadLEDBlue = 5;
int8_t solenoid = 8;
int8_t buzzer = 13;

int8_t joyB = 12;
int8_t joyG = 11;
int8_t joyH = 10;
int8_t joyD = 9;
int8_t joyPush = A0;
int8_t chargingHandle = A7;
int8_t BatteryRead = A1;

//set switch states to 0
int16_t triggerSwitch = 0;
int16_t selectorSwitch = 0;
int16_t chargerSwitch = 0;
int16_t handleSwitch = 0;
int16_t joyBPush = 0;
int16_t joyGPush = 0;
int16_t joyHPush = 0;
int16_t joyDPush = 0;
int16_t joyPushed = 0;

//local variables
int16_t bbrestChargeurValue;
int16_t bbrest;
int8_t alarmBB;
int8_t ROFFull;
int8_t ROFBurst;
int8_t burstBB;
int8_t semiMode;
int8_t fullMode;
int8_t timeBolt;
int16_t dwel;
int8_t verrTimer;
String modeValue;
int8_t menuValue = 0;
int8_t sousMenuValue = 0;
bool paramValuePlus = false;
bool paramValueMoins = false;
int16_t bbtire = 0;
long lastTempVerrouilage;
long tempsDever;
unsigned long previousMillisBolt = 0;
unsigned long currentTime;

//options
bool chargerOption;
bool handleOption;
bool buzzOption;
bool blocageVideOption;
bool alarmBBOption;
bool verEcranOption;
bool SnipeReady;
bool greenLightChargingHandleOption;
bool alarmBatOption;

//states
bool triggerStateFired = false;
bool sniperBlocked = false;
bool chargerState = false;
bool blocageState = false;
bool alarmLowPassed = false;
bool alarmEmptyPassed = false;
bool enterPressed = false;
bool enterPressedSave = false;
bool alarmBatLow = false;
bool ecranVerr = false;
bool appuieLong = false;

//Eeprom Addresses
int8_t ROFFullAdress = 0; //2
int8_t ROFBurstAdress = 2; //2
int8_t burstBBAdress = 4; //2
int8_t SnipeReadyAdress = 6; //1
int8_t timeBoltAdress = 7; //2
int8_t bbrestAdress = 9; //3
int8_t chargerOptionAdress = 12; //1
int8_t buzzOptionAdress = 13; //1
int8_t blocageVideAdress = 14; //1
int8_t alarmBBOptionAdress = 15; //1
int8_t alarmBBAdress = 16; //2
int8_t handleOptionAdress = 18; //1
int8_t greenLightHandleAdress = 19; //1
int8_t verrTimerAdress = 20; //3
int8_t dwelAdress = 23; //3
int8_t verEcranOptionAdress = 26; //1
int8_t alarmBatAdress = 27; //1
int8_t semiModeAdress = 28;//2
int8_t fullModeAdress = 30;//


//Class
VoltageCtrl voltCtrl;
Menu menu;
Alarm alarm;
Firing firing;

void setup() {

	Serial.begin(9600);

	pinMode(joyB, INPUT);
	pinMode(joyG, INPUT);
	pinMode(joyH, INPUT);
	pinMode(joyD, INPUT);
	pinMode(joyPush, INPUT);
	pinMode(chargingHandle, INPUT);
	pinMode(trigger, INPUT);
	pinMode(selector, INPUT);
	pinMode(charger, INPUT);
	pinMode(joyB, INPUT);
	pinMode(joyD, INPUT);
	pinMode(joyG, INPUT);
	pinMode(joyH, INPUT);
	pinMode(solenoid, OUTPUT);
	pinMode(reloadLEDRed, OUTPUT);
	pinMode(reloadLEDBlue, OUTPUT);
	pinMode(reloadLEDGreen, OUTPUT);
	digitalWrite(reloadLEDGreen, 0);
	digitalWrite(reloadLEDBlue, 0);
	digitalWrite(reloadLEDRed, 0);

	//Reading Eeprom Settings
	EEPROM.get(ROFFullAdress, ROFFull);
	EEPROM.get(ROFBurstAdress, ROFBurst);
	EEPROM.get(burstBBAdress, burstBB);
	EEPROM.get(bbrestAdress, bbrestChargeurValue);
	EEPROM.get(bbrestAdress, bbrest);
	EEPROM.get(alarmBBAdress, alarmBB);
	EEPROM.get(semiModeAdress, semiMode);
	EEPROM.get(fullModeAdress, fullMode);
	EEPROM.get(timeBoltAdress, timeBolt);
	EEPROM.get(dwelAdress, dwel);
	EEPROM.get(verrTimerAdress, verrTimer);
	EEPROM.get(chargerOptionAdress, chargerOption);
	EEPROM.get(handleOptionAdress, handleOption);
	EEPROM.get(buzzOptionAdress, buzzOption);
	EEPROM.get(blocageVideAdress, blocageVideOption);
	EEPROM.get(alarmBBOptionAdress, alarmBBOption);
	EEPROM.get(verEcranOptionAdress, verEcranOption);
	EEPROM.get(SnipeReadyAdress, SnipeReady);
	EEPROM.get(greenLightHandleAdress, greenLightChargingHandleOption);
	EEPROM.get(alarmBatAdress, alarmBatOption);

	menu.StartMenu(buzzer);
	lastTempVerrouilage = currentTime;
}

void loop() {
shoot: //step to by-pass non essentials functions
	currentTime = millis();

	double voltValue = voltCtrl.VoltageValue(BatteryRead);;
	triggerSwitch = digitalRead(trigger);
	selectorSwitch = digitalRead(selector);
	chargerSwitch = digitalRead(charger);
	handleSwitch = analogRead(chargingHandle);
	joyBPush = digitalRead(joyB);
	joyDPush = digitalRead(joyD);
	joyGPush = digitalRead(joyG);
	joyHPush = digitalRead(joyH);
	joyPushed = digitalRead(joyPush);

	//Fire mode displaying
	switch (selectorSwitch == HIGH ? fullMode : semiMode) {
	case 1:
		modeValue = "Semi";

		break;
	case 2:
		modeValue = "Burst " + String(burstBB);

		break;
	case 3:
		modeValue = "Full";

		break;
	case 4:
		modeValue = "Sniper";

		break;
	}

	//Firing
	if (triggerSwitch == HIGH && !triggerStateFired && chargerState && !blocageState && !alarmBatLow)
	{
		switch (selectorSwitch == HIGH ? fullMode : semiMode) {
		case 1:
			firing.Fire(solenoid, dwel);

			bbrest -= 1;
			bbtire += 1;

			triggerStateFired = true;
			break;
		case 2:

			for (int16_t x = 1; x <= burstBB; x++) {
				firing.Fire(solenoid, dwel);

				delay(1000 / ROFBurst);
			}

			bbrest -= burstBB;
			bbtire += burstBB;

			triggerStateFired = true;

			break;
		case 3:
			firing.Fire(solenoid, dwel);
			delay(1000 / ROFFull);

			bbrest -= 1;
			bbtire -= 1;

			break;
		case 4:
			if (!sniperBlocked) {
				firing.Fire(solenoid, dwel);

				bbrest -= 1;
				bbtire += 1;

				previousMillisBolt = currentTime;
			}

			triggerStateFired = true;
			sniperBlocked = true;

			int16_t delayBolt = timeBolt * 250;

			if (currentTime - previousMillisBolt >= delayBolt)
			{
				sniperBlocked = false;

				if (SnipeReady) {
					digitalWrite(reloadLEDGreen, 1);
					delay(10);
					digitalWrite(reloadLEDGreen, 0);
					delay(800);
				}
			}
			break;
		}

		menuValue = 0;
	}

	//Fire blocking when semi
	if (triggerSwitch == LOW && triggerStateFired)
	{
		triggerStateFired = false;
	}

	//Magazin Option
	if (chargerOption)
	{
		if (chargerSwitch == HIGH)
		{
			chargerState = true;
		}
		else
		{
			chargerState = false;
		}
	}
	else {
		chargerState = true;
	}

	//Empty mag option
	if (blocageVideOption)
	{
		if (bbrest <= 0)
		{
			blocageState = true;
		}
	}

	//BB's alarm
	if (alarmBBOption)
	{
		//"Empty BB's" Alarm
		if (bbrest <= 0 && alarmEmptyPassed == false)
		{
			alarmEmptyPassed = alarm.AlarmEmpty(reloadLEDRed);

			if (buzzOption == true)
			{
				alarm.BuzzerLow(buzzer);
			}
		}

		//"Near Empty" bb's alarm
		if (bbrest <= alarmBB && alarmLowPassed == false)
		{
			alarmLowPassed = alarm.AlarmLowBB(reloadLEDBlue);
		}
	}

	//testing trigger test to by-pass
	if (triggerSwitch == HIGH) {
		goto shoot; //by-passing
	}

	//Battery Voltage Alarm
	if (alarmBatOption)
	{
		if (voltCtrl.alarmVoltage(BatteryRead, currentTime))
		{
			alarm.AlarmBat(reloadLEDRed);

			alarmBatLow = true;

			if (buzzOption == true)
			{
				alarm.BuzzerBat(buzzer);
			}
		}
		else {
			alarmBatLow = false;
		}
	}

	//Charging Handle Option
	if (handleOption)
	{
		if (handleSwitch >= 1010)
		{
			alarmEmptyPassed = false;
			alarmLowPassed = false;

			blocageState = false;

			if (greenLightChargingHandleOption) {
				digitalWrite(reloadLEDGreen, 1);
				delay(10);
				digitalWrite(reloadLEDGreen, 0);
				delay(800);
			}

			bbrest = bbrestChargeurValue;
		}
	}

	//Screen lock
	if (verEcranOption)
	{
		int verTime = verrTimer * 1000;

		if ((currentTime - lastTempVerrouilage) > verTime && !ecranVerr)
		{
			menu.MenuVer();
			delay(1000);
			ecranVerr = true;
		}

		if ((currentTime - tempsDever) > 4000 && appuieLong)
		{
			menu.MenuDever();
			delay(1000);
			ecranVerr = false;
		}
	}

	//Reading joystick
	if (!ecranVerr) {
		if (joyBPush == HIGH)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (enterPressed)
			{
				paramValueMoins = true;
			}
			else {
				sousMenuValue = 0;

				if (menuValue == 0)
				{
					menuValue = 6;
				}
				else
				{
					menuValue = menuValue - 1;
				}

				lastTempVerrouilage = currentTime;
			}

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}

		if (joyHPush == HIGH)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (enterPressed)
			{
				paramValuePlus = true;
			}
			else {
				sousMenuValue = 0;

				if (menuValue == 6)
				{
					menuValue = 0;
				}
				else
				{
					menuValue = menuValue + 1;
				}
			}

			lastTempVerrouilage = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}

		if (joyDPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (sousMenuValue < 3)
			{
				sousMenuValue = sousMenuValue + 1;
			}

			lastTempVerrouilage = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}

		if (joyGPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (sousMenuValue > 0)
			{
				sousMenuValue = sousMenuValue - 1;
			}

			lastTempVerrouilage = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}
	}

	if (joyPushed)
	{
		digitalWrite(reloadLEDGreen, 1); //Lighting Green
		if (enterPressed)
		{
			enterPressed = false;
			enterPressedSave = true;
		}
		else if (enterPressed == false)
		{
			enterPressed = true;
			enterPressedSave = false;
		}

		if (ecranVerr == false)
		{
			lastTempVerrouilage = currentTime;
		}

		if (ecranVerr == true)
		{
			if (appuieLong == false)
			{
				tempsDever = currentTime;
				appuieLong = true;
			}
		}
		delay(200);
		digitalWrite(reloadLEDGreen, 0); //Delighting green
	}

	if (!joyPushed && appuieLong)
	{
		appuieLong = false;
	}

	//Menu's
	switch (menuValue)
	{
	case 0:
		menu.MainDisplay(voltValue, bbrest, bbrestChargeurValue, modeValue, bbtire);
		break;
	case 1:
		menu.MenuFullBurst(ROFFull, ROFBurst, burstBB, sousMenuValue);

		if (sousMenuValue == 0)
		{
			ROFFull = savingToEEPROM(ROFFullAdress, ROFFull, 1, 44);
		}

		if (sousMenuValue == 1)
		{
			ROFBurst = savingToEEPROM(ROFBurstAdress, ROFBurst, 1, 44);
		}

		if (sousMenuValue == 2)
		{
			burstBB = savingToEEPROM(burstBBAdress, burstBB, 1, 20);
		}

		break;
	case 2:
		menu.MenuSniper(timeBolt, SnipeReady, sousMenuValue);

		if (sousMenuValue == 0)
		{
			SnipeReady = savingToEEPROM(SnipeReadyAdress, SnipeReady);
		}

		if (sousMenuValue == 1)
		{
			timeBolt = savingToEEPROM(timeBoltAdress, timeBolt, 2, 9);
		}

		break;
	case 3:
		menu.MenuChargeur1(bbrestChargeurValue, chargerOption, buzzOption, blocageVideOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			bbrestChargeurValue = savingToEEPROM(bbrestAdress, bbrestChargeurValue, 1, 1999);
		}

		if (sousMenuValue == 1)
		{
			blocageVideOption = savingToEEPROM(blocageVideAdress, blocageVideOption);
		}

		if (sousMenuValue == 2)
		{
			chargerOption = savingToEEPROM(chargerOptionAdress, chargerOption);
		}

		if (sousMenuValue == 3)
		{
			buzzOption = savingToEEPROM(buzzOptionAdress, buzzOption);
		}

		break;
	case 4:
		menu.MenuChargeur2(alarmBBOption, alarmBB, handleOption, greenLightChargingHandleOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			alarmBBOption = savingToEEPROM(alarmBBOptionAdress, alarmBBOption);
		}

		if (sousMenuValue == 1)
		{
			alarmBB = savingToEEPROM(alarmBBAdress, alarmBB, 1, 19);
		}

		if (sousMenuValue == 2)
		{
			handleOption = savingToEEPROM(handleOptionAdress, handleOption);
		}

		if (sousMenuValue == 3)
		{
			greenLightChargingHandleOption = savingToEEPROM(greenLightHandleAdress, greenLightChargingHandleOption);
		}

		break;
	case 5:
		menu.MenuSetting(verrTimer, verEcranOption, alarmBatOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			verEcranOption = savingToEEPROM(verEcranOptionAdress, verEcranOption);
		}

		if (sousMenuValue == 1)
		{
			verrTimer = savingToEEPROM(verrTimerAdress, verrTimer, 30, 180);
		}

		if (sousMenuValue == 2)
		{
			alarmBatOption = savingToEEPROM(alarmBatAdress, alarmBatOption);
		}

		break;
	case 6:
		menu.MenuSetting2(semiMode, fullMode, dwel, sousMenuValue);

		if (sousMenuValue == 0)
		{
			semiMode = savingToEEPROM(semiModeAdress, semiMode, 2, 3);
		}

		if (sousMenuValue == 1)
		{
			fullMode = savingToEEPROM(fullModeAdress, fullMode, 2, 3);
		}

		if (sousMenuValue == 2)
		{
			dwel = savingToEEPROM(dwelAdress, dwel, 0, 199);
		}
		break;
	}

	paramValueMoins = false;
	paramValuePlus = false;
}

int16_t savingToEEPROM(int8_t eepromAddress, int16_t parameter, int16_t minValue, int16_t maxValue)
{
	if (enterPressed)
	{
		//Value modifying
		if (paramValueMoins && parameter >= minValue)
		{
			parameter -= 1;
		}
		else if (paramValuePlus && parameter <= maxValue)
		{
			parameter += 1;
		}
	}

	if (enterPressedSave)
	{
		//Saving in EEPROM
		EEPROM.put(eepromAddress, parameter);
		enterPressedSave = false;
	}
	return parameter;
}

bool savingToEEPROM(int8_t eepromAddress, bool parameter)
{
	if (enterPressed)
	{
		//Value modifying
		if (paramValueMoins && parameter)
		{
			parameter = false;
		}
		else if (paramValuePlus && !parameter)
		{
			parameter = true;
		}
	}

	if (enterPressedSave)
	{
		//Saving in EEPROM
		EEPROM.put(eepromAddress, parameter);
		enterPressedSave = false;
	}
	return parameter;
}
