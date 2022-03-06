// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "arduino.h"

class Menu {
public:
	Menu();
	void StartMenu(int8_t buzzer);
	void MainMenu(double voltValue, int16_t bbsLeft, int16_t bbrestChargeur, String modeValue, int16_t bbtire);
	void FullBurstMenu(int8_t ROFFull, int8_t ROFBurst, int8_t BurstBB, int8_t subMenuValue);
	void SniperMenu(int8_t timeBolt, bool greenLed, int8_t subMenuValue);
	void MagMenu1(int16_t chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int8_t subMenuValue);
	void MagMenu2(bool alarm, int8_t alarmLowBB, bool chargingHandle, bool greenLight, int8_t subMenuValue);
	void SettingsMenu1(int8_t veille, bool verrou, bool LowBat, int8_t subMenuValue);
	void SettingMenu2(int8_t semi, int8_t full, int16_t dwel, int8_t subMenuValue);
	void UnlockDisplay();
	void lockDisplay();
};

#endif
