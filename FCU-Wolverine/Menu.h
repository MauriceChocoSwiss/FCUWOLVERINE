// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "arduino.h"

class Menu {
public:
	Menu();
	void StartMenu(uint8_t buzzer);
	void MainMenu(double voltValue, int16_t bbsLeft, uint16_t bbrestChargeur, String modeValue, uint16_t bbtire);
	void FullBurstMenu(uint8_t ROFFull, uint8_t ROFBurst, uint8_t BurstBB, uint8_t subMenuValue);
	void SniperMenu(uint8_t timeBolt, bool greenLed, uint8_t subMenuValue);
	void MagMenu1(uint16_t chargeurCap, bool switchchargeur, bool buzzer, bool blocage, uint8_t subMenuValue);
	void MagMenu2(bool alarm, uint8_t alarmLowBB, bool chargingHandle, bool greenLight, uint8_t subMenuValue);
	void SettingsMenu1(uint8_t veille, bool verrou, bool LowBat, uint8_t subMenuValue);
	void SettingMenu2(uint8_t semi, uint8_t full, uint16_t dwel, uint8_t subMenuValue);
	void UnlockDisplay();
	void lockDisplay();
};

#endif
