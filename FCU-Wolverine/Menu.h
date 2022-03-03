// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "arduino.h"

class Menu {
public:
	Menu();
	void StartMenu(int8_t buzzer);
	void MainDisplay(double voltValue, int16_t bbrest, int16_t bbrestChargeur, String modeValue, int16_t bbtire);
	void MenuFullBurst(int8_t ROFFull, int8_t ROFBurst, int8_t BurstBB, int8_t sousMenuValue);
	void MenuSniper(int8_t timeBolt, bool greenLed, int8_t sousMenuValue);
	void MenuChargeur1(int16_t chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int8_t sousMenuValue);
	void MenuChargeur2(bool alarm, int8_t alarmLowBB, bool chargingHandle, bool greenLight, int8_t sousMenuValue);
	void MenuSetting(int8_t veille, bool verrou, bool LowBat, int8_t sousMenuValue);
	void MenuSetting2(int8_t semi, int8_t full, int16_t dwel, int8_t sousMenuValue);
	void MenuDever();
	void MenuVer();
};

#endif
