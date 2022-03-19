#include "Alarm.h"
#include "Menu.h"
#include "VoltageCtrl.h"
#include "Firing.h"
#include <EEPROM.h>

//pin assignment
int trigger = 2;
int8_t selector = 3;
int8_t magazine = 4;
int8_t reloadLEDRed = 5;
int8_t reloadLEDGreen = 6;
int8_t reloadLEDBlue = 7;
int8_t solenoid = 8;
int8_t buzzer = 13;

int8_t joyBottom = 12;
int8_t joyLeft = 11;
int8_t joyUp = 10;
int8_t joyRight = 9;
int8_t joyPush = A0;
int8_t chargingHandle = A7;
int8_t batteryReading = A1;

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
int16_t bbsLeftMagValue;
int16_t bbsLeft;
int8_t alarmBB;
int8_t ROFFull;
int8_t ROFBurst;
int8_t burstBB;
int8_t semiMode;
int8_t fullMode;
int8_t timeBolt;
int16_t dwel;
int8_t screenLockTimer;
String modeValue;
int8_t menuValue = 0;
int8_t subMenuValue = 0;
bool paramValuePlus = false;
bool paramValueMoins = false;
int16_t bbtire = 0;
long screenLockLastTimer;
long screenUnlockTimer;
unsigned long previousMillisBolt = 0;
unsigned long currentTime;

//options
bool magOption;
bool handleOption;
bool buzzOption;
bool emptyMagLockOption;
bool alarmBBOption;
bool screenLockOption;
bool SnipeReady;
bool greenLightChargingHandleOption;
bool alarmBatOption;

//states
bool triggerStateFired = false;
bool sniperBlocked = false;
bool magState = false;
bool emptyMagBlockingState = false;
bool alarmLowPassed = false;
bool alarmEmptyPassed = false;
bool enterPressed = false;
bool enterPressedSave = false;
bool alarmBatLow = false;
bool screenLocked = false;
bool longPress = false;

//Eeprom Addresses
int8_t ROFFullAdress = 0; //2
int8_t ROFBurstAdress = 2; //2
int8_t burstBBAdress = 4; //2
int8_t SnipeReadyAdress = 6; //1
int8_t timeBoltAdress = 7; //2
int8_t bbrestAdress = 9; //3
int8_t magOptionAdress = 12; //1
int8_t buzzOptionAdress = 13; //1
int8_t emptyMagLockingAdress = 14; //1
int8_t alarmBBOptionAdress = 15; //1
int8_t alarmBBAdress = 16; //2
int8_t handleOptionAdress = 18; //1
int8_t greenLightHandleAdress = 19; //1
int8_t screenLockTimerAdress = 20; //3
int8_t dwelAdress = 23; //3
int8_t screenLockOptionAdress = 26; //1
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

	pinMode(joyBottom, INPUT);
	pinMode(joyLeft, INPUT);
	pinMode(joyUp, INPUT);
	pinMode(joyRight, INPUT);
	pinMode(joyPush, INPUT);
	pinMode(chargingHandle, INPUT);
	pinMode(trigger, INPUT);
	pinMode(selector, INPUT);
	pinMode(magazine, INPUT);
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
	EEPROM.get(bbrestAdress, bbsLeftMagValue);
	EEPROM.get(bbrestAdress, bbsLeft);
	EEPROM.get(alarmBBAdress, alarmBB);
	EEPROM.get(semiModeAdress, semiMode);
	EEPROM.get(fullModeAdress, fullMode);
	EEPROM.get(timeBoltAdress, timeBolt);
	EEPROM.get(dwelAdress, dwel);
	EEPROM.get(screenLockTimerAdress, screenLockTimer);
	EEPROM.get(magOptionAdress, magOption);
	EEPROM.get(handleOptionAdress, handleOption);
	EEPROM.get(buzzOptionAdress, buzzOption);
	EEPROM.get(emptyMagLockingAdress, emptyMagLockOption);
	EEPROM.get(alarmBBOptionAdress, alarmBBOption);
	EEPROM.get(screenLockOptionAdress, screenLockOption);
	EEPROM.get(SnipeReadyAdress, SnipeReady);
	EEPROM.get(greenLightHandleAdress, greenLightChargingHandleOption);
	EEPROM.get(alarmBatAdress, alarmBatOption);

	menu.StartMenu(buzzer);
	screenLockLastTimer = currentTime;
}

void loop() {
shoot: //step to by-pass non essentials functions
	currentTime = millis();

	double voltValue = voltCtrl.VoltageValue(batteryReading);;
	triggerSwitch = digitalRead(trigger);
	selectorSwitch = digitalRead(selector);
	chargerSwitch = digitalRead(magazine);
	handleSwitch = analogRead(chargingHandle);
	joyBPush = digitalRead(joyBottom);
	joyDPush = digitalRead(joyRight);
	joyGPush = digitalRead(joyLeft);
	joyHPush = digitalRead(joyUp);
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
	if (triggerSwitch == HIGH && !triggerStateFired && magState && !emptyMagBlockingState && !alarmBatLow)
	{
		switch (selectorSwitch == HIGH ? fullMode : semiMode) {
		case 1:
			firing.Fire(solenoid, dwel);

			bbsLeft -= 1;
			bbtire += 1;

			triggerStateFired = true;
			break;
		case 2:

			for (int16_t x = 1; x <= burstBB; x++) {
				firing.Fire(solenoid, dwel);

				delay(1000 / ROFBurst);
			}

			bbsLeft -= burstBB;
			bbtire += burstBB;

			triggerStateFired = true;

			break;
		case 3:
			firing.Fire(solenoid, dwel);
			delay(1000 / ROFFull);

			bbsLeft -= 1;
			bbtire -= 1;

			break;
		case 4:
			if (!sniperBlocked) {
				firing.Fire(solenoid, dwel);

				bbsLeft -= 1;
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
	if (magOption)
	{
		if (chargerSwitch == HIGH)
		{
			magState = true;
		}
		else
		{
			magState = false;
		}
	}
	else {
		magState = true;
	}

	//Empty mag option
	if (emptyMagLockOption)
	{
		if (bbsLeft <= 0)
		{
			emptyMagBlockingState = true;
		}
	}

	//BB's alarm
	if (alarmBBOption)
	{
		//"Empty BB's" Alarm
		if (bbsLeft <= 0 && alarmEmptyPassed == false)
		{
			alarmEmptyPassed = alarm.AlarmEmpty(reloadLEDRed);

			if (buzzOption == true)
			{
				alarm.BuzzerLow(buzzer);
			}
		}

		//"Near Empty" bb's alarm
		if (bbsLeft <= alarmBB && alarmLowPassed == false)
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
		if (voltCtrl.alarmVoltage(batteryReading, currentTime))
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

			emptyMagBlockingState = false;

			if (greenLightChargingHandleOption) {
				digitalWrite(reloadLEDGreen, 1);
				delay(10);
				digitalWrite(reloadLEDGreen, 0);
				delay(800);
			}

			bbsLeft = bbsLeftMagValue;
		}
	}

	//Screen lock
	if (screenLockOption)
	{
		int verTime = screenLockTimer * 1000;

		if ((currentTime - screenLockLastTimer) > verTime && !screenLocked)
		{
			menu.lockDisplay();
			delay(1000);
			screenLocked = true;
		}

		if ((currentTime - screenUnlockTimer) > 4000 && longPress)
		{
			menu.UnlockDisplay();
			delay(1000);
			screenLocked = false;
		}
	}

	//Reading joystick
	if (!screenLocked) {
		if (joyBPush == HIGH)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (enterPressed)
			{
				paramValueMoins = true;
			}
			else {
				subMenuValue = 0;

				if (menuValue == 0)
				{
					menuValue = 6;
				}
				else
				{
					menuValue = menuValue - 1;
				}

				screenLockLastTimer = currentTime;
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
				subMenuValue = 0;

				if (menuValue == 6)
				{
					menuValue = 0;
				}
				else
				{
					menuValue = menuValue + 1;
				}
			}

			screenLockLastTimer = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}

		if (joyDPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (subMenuValue < 3)
			{
				subMenuValue = subMenuValue + 1;
			}

			screenLockLastTimer = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen, 0); //Delighting green
		}

		if (joyGPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen, 1); //Lighting Green

			if (subMenuValue > 0)
			{
				subMenuValue = subMenuValue - 1;
			}

			screenLockLastTimer = currentTime;

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

		if (screenLocked == false)
		{
			screenLockLastTimer = currentTime;
		}

		if (screenLocked == true)
		{
			if (longPress == false)
			{
				screenUnlockTimer = currentTime;
				longPress = true;
			}
		}
		delay(200);
		digitalWrite(reloadLEDGreen, 0); //Delighting green
	}

	if (!joyPushed && longPress)
	{
		longPress = false;
	}

	//Menu's
	switch (menuValue)
	{
	case 0:
		menu.MainMenu(voltValue, bbsLeft, bbsLeftMagValue, modeValue, bbtire);
		break;
	case 1:
		menu.FullBurstMenu(ROFFull, ROFBurst, burstBB, subMenuValue);

		if (subMenuValue == 0)
		{
			ROFFull = savingToEEPROM(ROFFullAdress, ROFFull, 1, 44);
		}

		if (subMenuValue == 1)
		{
			ROFBurst = savingToEEPROM(ROFBurstAdress, ROFBurst, 1, 44);
		}

		if (subMenuValue == 2)
		{
			burstBB = savingToEEPROM(burstBBAdress, burstBB, 1, 20);
		}

		break;
	case 2:
		menu.SniperMenu(timeBolt, SnipeReady, subMenuValue);

		if (subMenuValue == 0)
		{
			SnipeReady = savingToEEPROM(SnipeReadyAdress, SnipeReady);
		}

		if (subMenuValue == 1)
		{
			timeBolt = savingToEEPROM(timeBoltAdress, timeBolt, 2, 9);
		}

		break;
	case 3:
		menu.MagMenu1(bbsLeftMagValue, magOption, buzzOption, emptyMagLockOption, subMenuValue);

		if (subMenuValue == 0)
		{
			bbsLeftMagValue = savingToEEPROM(bbrestAdress, bbsLeftMagValue, 1, 1999);
		}

		if (subMenuValue == 1)
		{
			emptyMagLockOption = savingToEEPROM(emptyMagLockingAdress, emptyMagLockOption);
		}

		if (subMenuValue == 2)
		{
			magOption = savingToEEPROM(magOptionAdress, magOption);
		}

		if (subMenuValue == 3)
		{
			buzzOption = savingToEEPROM(buzzOptionAdress, buzzOption);
		}

		break;
	case 4:
		menu.MagMenu2(alarmBBOption, alarmBB, handleOption, greenLightChargingHandleOption, subMenuValue);

		if (subMenuValue == 0)
		{
			alarmBBOption = savingToEEPROM(alarmBBOptionAdress, alarmBBOption);
		}

		if (subMenuValue == 1)
		{
			alarmBB = savingToEEPROM(alarmBBAdress, alarmBB, 1, 19);
		}

		if (subMenuValue == 2)
		{
			handleOption = savingToEEPROM(handleOptionAdress, handleOption);
		}

		if (subMenuValue == 3)
		{
			greenLightChargingHandleOption = savingToEEPROM(greenLightHandleAdress, greenLightChargingHandleOption);
		}

		break;
	case 5:
		menu.SettingsMenu1(screenLockTimer, screenLockOption, alarmBatOption, subMenuValue);

		if (subMenuValue == 0)
		{
			screenLockOption = savingToEEPROM(screenLockOptionAdress, screenLockOption);
		}

		if (subMenuValue == 1)
		{
			screenLockLastTimer = savingToEEPROM(screenLockTimerAdress, screenLockTimer, 30, 180);
		}

		if (subMenuValue == 2)
		{
			alarmBatOption = savingToEEPROM(alarmBatAdress, alarmBatOption);
		}

		break;
	case 6:
		menu.SettingMenu2(semiMode, fullMode, dwel, subMenuValue);

		if (subMenuValue == 0)
		{
			semiMode = savingToEEPROM(semiModeAdress, semiMode, 2, 3);
		}

		if (subMenuValue == 1)
		{
			fullMode = savingToEEPROM(fullModeAdress, fullMode, 2, 3);
		}

		if (subMenuValue == 2)
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
