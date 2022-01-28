// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "arduino.h"

class Menu {
public:
	Menu();
	void StartMenu(int8_t buzzer);
	void MainDisplay(double voltValue, int8_t bbrest, int8_t bbrestChargeur, String modeValue, int8_t bbtire);
	void MenuFullBurst(int8_t ROFFull, int8_t ROFBurst, int8_t QteBB, int8_t sousMenuValue);
	void MenuSniper(int8_t timeBolt, bool greenLed, int8_t sousMenuValue);
	void MenuChargeur1(int8_t chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int8_t sousMenuValue);
	void MenuChargeur2(bool alarm, int8_t alarmLowBB, bool chargingHandle, bool greenLight, int8_t sousMenuValue);
	void MenuSetting(int8_t veille, bool verrou, bool LowBat, int8_t sousMenuValue);
	void MenuSetting2(int8_t semi, int8_t full, int8_t dwel, int8_t sousMenuValue);
	void MenuDever();
	void MenuVer();
};

#endif
