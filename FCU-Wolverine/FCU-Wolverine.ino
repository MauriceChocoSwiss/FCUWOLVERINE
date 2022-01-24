#include "Alarm.h"
#include "Menu.h"
#include "VoltageCtrl.h"
#include "SelectorOnBurst.h"
#include "SelectorOnFull.h"
#include "SelectorOnSemi.h"
#include "armed.h"
#include <Wire.h>
#include <EEPROM.h>

//assignement des pin
int trigger = 2;
int selector = 3;
int charger = 4;
int reloadLEDRed = 7;
int reloadLEDGreen = 6;
int reloadLEDBlue = 5;
int solenoid = 8;
int buzzer = 13;

int joyB = 12;
int joyG = 11;
int joyH = 10;
int joyD = 9;
int joyPush = A0;
int chargingHandle = A7;
int BatteryRead = A1;

//mise des �tats des switchs a zero
int triggerSwitch = 0;
int selectorSwitch = 0;
int chargerSwitch = 0;
int handleSwitch = 0;
int joyBPush = 0;
int joyGPush = 0;
int joyHPush = 0;
int joyDPush = 0;
int joyPushed = 0;

//d�claration des variables locales
int bbrestChargeurValue;
int bbrest;
int alarmBB;
int ROFFull;
int ROF;
int burstBB;
int semiMode;
int fullMode;
int timeBolt;
int dwel;
int verrTimer;
String modeValue;
int menuValue = 0;
int sousMenuValue = 0;
bool paramValueP = false;
bool paramValueM = false;
int bbtire = 0;
long lastTempVerrouilage;
long tempsDever;
unsigned long previousMillis1 = 0;
unsigned long currentTime;

//definition des options
bool chargerOption;
bool handleOption;
bool buzzOption;
bool blocageVideOption;
bool alarmBBOption;
bool verEcranOption;
bool SnipeReady;
bool greenLightChargingHandleOption;
bool alarmBatOption;

//etat
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

//d�claratgion des adresse des parametre dans l'eeprom
int ROFFullAdress = 0; //2
int ROFBurstAdress = 2; //2
int burstBBAdress = 4; //2
int SnipeReadyAdress = 6; //1
int timeBoltAdress = 7; //2
int bbrestAdress = 9; //3
int chargerOptionAdress = 12; //1
int buzzOptionAdress = 13; //1
int blocageVideAdress = 14; //1
int alarmBBOptionAdress = 15; //1
int alarmBBAdress = 16; //2
int handleOptionAdress = 18; //1
int greenLightHandleAdress = 19; //1
int verrTimerAdress = 20; //3
int dwelAdress = 23; //3
int verEcranOptionAdress = 26; //1
int alarmBatAdress = 27; //1
int semiModeAdress = 28;//2
int fullModeAdress = 30;//


//d�claration des classes
SelectorOnSemi semi;
Armed armed;
SelectorOnFull full;
SelectorOnBurst burst;
VoltageCtrl voltCtrl;
Menu menu;
Alarm alarm;

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

//	EEPROM.put(ROFFullAdress, 15);
//  EEPROM.put(fullModeAdress, 3);
//	EEPROM.put(dwelAdress, 12);

	//lecture des settings de l'eeprom
	EEPROM.get(ROFFullAdress, ROFFull);
	EEPROM.get(ROFBurstAdress, ROF);
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

//	Serial.println(ROFFull); delay(100);
//	Serial.println(ROF); delay(100); //"Rof : " +
//	Serial.println(burstBB); delay(100);//"Burst BB : " + 
//	Serial.println(bbrestChargeurValue); delay(100); //"bb rest Chargeur : " + 
//	Serial.println(bbrest); delay(100);//"bb rest : " + 
//	Serial.println(alarmBB); delay(100);
//	Serial.println(semiMode); delay(100);
//	Serial.println(fullMode); delay(100);
//	Serial.println(timeBolt); delay(100);
//	Serial.println(dwel); delay(100);
//	Serial.println(verrTimer); delay(100);
//	Serial.println(chargerOption); delay(100);
//	Serial.println(handleOption); delay(100);
//	Serial.println(buzzOption); delay(100);
//	Serial.println(blocageVideOption); delay(100);
//	Serial.println(alarmBBOption); delay(100);
//	Serial.println(verEcranOption); delay(100);
//	Serial.println(SnipeReady); delay(100);
//	Serial.println(greenLightChargingHandleOption); delay(100);
//	Serial.println(alarmBatOption); delay(100);

	menu.StartMenu(buzzer);
	lastTempVerrouilage = currentTime;
}

void loop() {
	testtir: //etape pour by-pass la partie du code non necessaire au tir
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
	joyPushed = analogRead(joyPush);

	//Affichage du mode de tir
	//Selecteur sur FULL
	if (selectorSwitch == HIGH)
	{
		switch (fullMode) {
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
	}
	//selecteur sur SEMI
	else if (selectorSwitch == LOW)
	{
		switch (semiMode) {
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
	}


	//Tir
	if (triggerSwitch == HIGH && triggerStateFired == false && chargerState == true && blocageState == false && alarmBatLow == false)
	{
		//Selecteur sur SEMI
		if (selectorSwitch == LOW)
		{
			switch (semiMode) {
			case 1:
				semi.selectorSemi(solenoid, dwel);

				bbrest = bbrest - 1;
				bbtire = bbtire + 1;

				triggerStateFired = true;
				break;
			case 2:
				triggerStateFired = burst.selectorBurst(solenoid, dwel, ROF, burstBB);

				bbrest = bbrest - burstBB;
				bbtire = bbtire + burstBB;

				break;
			case 3:
				full.selectorFull(solenoid, dwel, ROFFull);

				bbrest = bbrest - 1;
				bbtire = bbtire + 1;

				break;
			case 4:
				if (!sniperBlocked) {
					semi.selectorSemi(solenoid, dwel);

					bbrest = bbrest - 1;
					bbtire = bbtire + 1;

					previousMillis1 = currentTime;
				}

				triggerStateFired = true;
				sniperBlocked = true;

				int delay = timeBolt * 250;

				if (currentTime - previousMillis1 >= delay)
				{
					sniperBlocked = false;

					if (SnipeReady) {
						armed.armed(reloadLEDGreen);
					}
				}
				break;
			}
		}

//		//selecteur sur FULL
		else if (selectorSwitch == HIGH)
		{
			switch (fullMode) {
			case 1:
  			semi.selectorSemi(solenoid, dwel);

				bbrest = bbrest - 1;
				bbtire = bbtire + 1;

				triggerStateFired = true;

				break;
			case 2:
				triggerStateFired = burst.selectorBurst(solenoid, dwel, ROF, burstBB);

				bbrest = bbrest - burstBB;
				bbtire = bbtire + burstBB;

				break;
			case 3:
				full.selectorFull(solenoid, dwel, ROFFull);

				bbrest = bbrest - 1;
				bbtire = bbtire + 1;

				break;
			case 4:
				if (!sniperBlocked) {
					semi.selectorSemi(solenoid, dwel);

					bbrest = bbrest - 1;
					bbtire = bbtire + 1;

					previousMillis1 = currentTime;
				}

				triggerStateFired = true;
				sniperBlocked = true;

				int delay = timeBolt * 250;

				if (currentTime - previousMillis1 >= delay)
				{
					sniperBlocked = false;

					if (SnipeReady) {
						armed.armed(reloadLEDGreen);
					}
				}
			}
		}

		menuValue = 0;
	}

	//Blocage des tirs pour le semi
	if (triggerSwitch == LOW && triggerStateFired == true)
	{
		triggerStateFired = false;
	}

	//Option relatives au chargeur
	if (chargerOption == true)
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

	//Option blocage si compteur a 0
	if (blocageVideOption == true)
	{
		if (bbrest <= 0)
		{
			blocageState = true;
		}
	}

	//Option Charging Handle
	if (handleOption == true)
	{
		if (handleSwitch >= 1010)
		{
			alarmEmptyPassed = false;
			alarmLowPassed = false;

			blocageState = false;

			if (greenLightChargingHandleOption) {
				armed.armed(reloadLEDGreen);
			}

			bbrest = bbrestChargeurValue;
		}
	}

	//Alarmes pour les billes
	if (alarmBBOption == true)
	{
		//Alarme "Plus de billes"
		if (bbrest <= 0)
		{
			alarmEmptyPassed = alarm.AlarmEmpty(reloadLEDRed);

			if (buzzOption == true)
			{
				alarm.BuzzerLow(buzzer);
			}
		}
		else
                {
                  alarmEmptyPassed = false;
                  alarmLowPassed = false;
                  digitalWrite(reloadLEDGreen, 0);
                  digitalWrite(reloadLEDBlue, 0);
                  digitalWrite(reloadLEDRed, 0);
                }

		//Alarme "Presque plus de billes"
		if (bbrest <= alarmBB)
		{
			alarmLowPassed = alarm.AlarmLowBB(reloadLEDBlue);
		}
		else
                {
                  alarmLowPassed = false;
                  digitalWrite(reloadLEDGreen, 0);
                  digitalWrite(reloadLEDBlue, 0);
                  digitalWrite(reloadLEDRed, 0);
                }
	}

	//verrouillage de l'�cran
	if (verEcranOption == true)
	{
		int verTime = verrTimer * 1000;

		if ((currentTime - lastTempVerrouilage) > verTime && ecranVerr == false)
		{
			ecranVerr = true;

			if (currentTime - lastTempVerrouilage <= 1500)
			{
				menu.MenuVer();
			}
		}

		if ((currentTime - tempsDever) > 4000 && appuieLong)
		{
			ecranVerr = false;
			if (currentTime - tempsDever <= 1500)
			{
				menu.MenuDever();
			}
		}
	}

	//Alarme Tension Batterie
	if (alarmBatOption == true)
	{
		if (voltCtrl.alarmVoltage(BatteryRead))
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
	
	if (triggerSwitch == HIGH) { //test la queue de detente pour by-pass la suite du code
          goto testtir; //retourne au debut du code
	}

	//lecture du JoyStick
	if (ecranVerr == false) {
		if (joyBPush == HIGH)
		{
			digitalWrite(reloadLEDGreen,1); //allume la LED verte
			if (enterPressed)
			{
				paramValueM = true;
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
			digitalWrite(reloadLEDGreen,0); //eteind la LED verte
		}

		if (joyHPush == HIGH)
		{
			digitalWrite(reloadLEDGreen,1); //allume la LED verte
			if (enterPressed)
			{
				paramValueP = true;
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
			digitalWrite(reloadLEDGreen,0); //eteind la LED verte
		}

		if (joyDPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen,1); //allume la LED verte
			if (sousMenuValue < 3)
			{
				sousMenuValue = sousMenuValue + 1;
			}

			lastTempVerrouilage = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen,0); //eteind la LED verte
		}

		if (joyGPush == HIGH && enterPressed == false)
		{
			digitalWrite(reloadLEDGreen,1); //allume la LED verte
			if (sousMenuValue > 0)
			{
				sousMenuValue = sousMenuValue - 1;
			}

			lastTempVerrouilage = currentTime;

			delay(200);
			digitalWrite(reloadLEDGreen,0); //eteind la LED verte
		}
	}

	if (joyPushed >= 1005)
	{
		digitalWrite(reloadLEDGreen,1); //allume la LED verte
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

		delay(100);
		digitalWrite(reloadLEDGreen,0); //eteind la LED verte
	}

	if (joyPushed <= 900 && appuieLong == true)
	{
		appuieLong = false;
	}

	//affichage du menu
	switch (menuValue)
	{
	case 0:
		menu.MainDisplay(voltValue, bbrest, bbrestChargeurValue, modeValue, bbtire);
		break;
	case 1:
		menu.MenuFullBurst(ROFFull, ROF, burstBB, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && ROFFull >= 1)
				{
					ROFFull = ROFFull - 1;
				}
				else if (paramValueP && ROFFull <= 44)
				{
					ROFFull = ROFFull + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(ROFFullAdress, ROFFull);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && ROF >= 1)
				{
					ROF = ROF - 1;
				}
				else if (paramValueP && ROF <= 44)
				{
					ROF = ROF + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(ROFBurstAdress, ROF);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 2)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && burstBB >= 1)
				{
					burstBB = burstBB - 1;
				}
				else if (paramValueP && burstBB <= 5)
				{
					burstBB = burstBB + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(burstBBAdress, burstBB);
				enterPressedSave = false;
			}
		}

		break;
	case 2:
		menu.MenuSniper(timeBolt, SnipeReady, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && SnipeReady)
				{
					SnipeReady = false;
				}
				else if (paramValueP && !SnipeReady)
				{
					SnipeReady = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(SnipeReadyAdress, SnipeReady);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && timeBolt >= 2)
				{
					timeBolt = timeBolt - 1;
				}
				else if (paramValueP && timeBolt <= 9)
				{
					timeBolt = timeBolt + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(timeBoltAdress, timeBolt);
				enterPressedSave = false;
			}
		}

		break;
	case 3:
		menu.MenuChargeur1(bbrestChargeurValue, chargerOption, buzzOption, blocageVideOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && bbrestChargeurValue >= 1)
				{
					bbrestChargeurValue = bbrestChargeurValue - 1;
				}
				else if (paramValueP && bbrestChargeurValue <= 1999)
				{
					bbrestChargeurValue = bbrestChargeurValue + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(bbrestAdress, bbrestChargeurValue);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && blocageVideOption)
				{
					blocageVideOption = false;
				}
				else if (paramValueP && !blocageVideOption)
				{
					blocageVideOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(blocageVideAdress, blocageVideOption);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 2)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && chargerOption)
				{
					chargerOption = false;
				}
				else if (paramValueP && !chargerOption)
				{
					chargerOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(chargerOptionAdress, chargerOption);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 3)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && buzzOption)
				{
					buzzOption = false;
				}
				else if (paramValueP && !buzzOption)
				{
					buzzOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(buzzOptionAdress, buzzOption);
				enterPressedSave = false;
			}
		}

		break;
	case 4:
		menu.MenuChargeur2(alarmBBOption, alarmBB, handleOption, greenLightChargingHandleOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && alarmBBOption)
				{
					alarmBBOption = false;
				}
				else if (paramValueP && !alarmBBOption)
				{
					alarmBBOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(alarmBBOptionAdress, alarmBBOption);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && alarmBB >= 1)
				{
					alarmBB = alarmBB - 1;
				}
				else if (paramValueP && alarmBB <= 19)
				{
					alarmBB = alarmBB + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(alarmBBAdress, alarmBB);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 2)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && handleOption)
				{
					handleOption = false;
				}
				else if (paramValueP && !handleOption)
				{
					handleOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(handleOptionAdress, handleOption);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 3)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && greenLightChargingHandleOption)
				{
					greenLightChargingHandleOption = false;
				}
				else if (paramValueP && !greenLightChargingHandleOption)
				{
					greenLightChargingHandleOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(greenLightHandleAdress, greenLightChargingHandleOption);
				enterPressedSave = false;
			}
		}

		break;
	case 5:
		menu.MenuSetting(verrTimer, verEcranOption, alarmBatOption, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && verEcranOption)
				{
					verEcranOption = false;
				}
				else if (paramValueP && !verEcranOption)
				{
					verEcranOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(verEcranOptionAdress, verEcranOption);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && verrTimer >= 30)
				{
					verrTimer = verrTimer - 30;
				}
				else if (paramValueP && verrTimer <= 180)
				{
					verrTimer = verrTimer + 30;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(verrTimerAdress, verrTimer);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 2)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && alarmBatOption)
				{
					alarmBatOption = false;
				}
				else if (paramValueP && !alarmBatOption)
				{
					alarmBatOption = true;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(alarmBatAdress, alarmBatOption);
				enterPressedSave = false;
			}
		}

		break;
	case 6:
		menu.MenuSetting2(semiMode, fullMode, dwel, sousMenuValue);

		if (sousMenuValue == 0)
		{
			if (enterPressed)
			{
				//modification de valeur
				if (paramValueM && semiMode >= 2)
				{
					semiMode = semiMode - 1;
				}
				else if (paramValueP && semiMode <= 3)
				{
					semiMode = semiMode + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(semiModeAdress, semiMode);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 1)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && fullMode >= 2)
				{
					fullMode = fullMode - 1;
				}
				else if (paramValueP && fullMode <= 3)
				{
					fullMode = fullMode + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(fullModeAdress, fullMode);
				enterPressedSave = false;
			}
		}

		if (sousMenuValue == 2)
		{
			if (enterPressed)
			{
				//modification de valeur

				if (paramValueM && dwel >= 0)
				{
					dwel = dwel - 1;
				}
				else if (paramValueP && dwel <= 199)
				{
					dwel = dwel + 1;
				}
			}

			if (enterPressedSave)
			{
				//Save dans l'EEPROM
				EEPROM.put(dwelAdress, dwel);
				enterPressedSave = false;
			}
		}
		break;
	}

	paramValueM = false;
	paramValueP = false;
}
