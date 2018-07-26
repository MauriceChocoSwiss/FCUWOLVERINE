// Menu.h

#ifndef _MENU_h
#define _MENU_h

#include "arduino.h"

class Menu {
public:
	Menu();
	void StartMenu(int buzzer);
	void MainDisplay(double voltValue, int bbrest, int bbrestChargeur, String modeValue, int bbtire);
	void MenuFullBurst(int ROFFull, int ROFBurst, int QteBB, int sousMenuValue);
	void MenuSniper(int timeBolt, bool greenLed, int sousMenuValue);
	void MenuChargeur1(int chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int sousMenuValue);
	void MenuChargeur2(bool alarm, int alarmLowBB, bool chargingHandle, bool greenLight, int sousMenuValue);
	void MenuSetting(int veille, bool verrou, bool LowBat, int sousMenuValue);
	void MenuSetting2(int semi, int full, int dwel, int sousMenuValue);
};

#endif

