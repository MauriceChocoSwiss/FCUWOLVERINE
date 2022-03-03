//#include <U8x8lib.h>
#include <U8g2lib.h>
#include "Menu.h"
#include <Wire.h>

//U8X8_SSD1306_128X32_UNIVISION_HW_I2C displayMenu(U8X8_PIN_NONE, A5, A4);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C displayMenu(U8G2_R2);

Menu::Menu() {
}

void Menu::StartMenu(int8_t buzzer) {
	displayMenu.begin();  // initialize with the I2C addr 0x3D (for the 128x64) 
  
	displayMenu.setFont(u8g2_font_6x10_mr);

  displayMenu.clearBuffer();
	// text display tests
 displayMenu.setCursor(20, 12);
	displayMenu.print("Hello Soldier !");
  displayMenu.sendBuffer();
	delay(3000);
  
	displayMenu.clearBuffer();
  displayMenu.setCursor(30, 12);
	displayMenu.print("Let's Play !");
  displayMenu.sendBuffer();
  
	delay(1000);
	tone(buzzer, 2000, 500);
	delay(1000);
	noTone(buzzer);
	displayMenu.clearBuffer();

}

void Menu::MainDisplay(double voltValue, int16_t bbrest, int16_t bbrestChargeur, String modeValue, int16_t bbtire)
{
  displayMenu.clearBuffer();
	displayMenu.setCursor(0, 8);
	displayMenu.print("BB:");
	displayMenu.print(bbrest);
	displayMenu.print("|");
	displayMenu.print(bbrestChargeur);
  displayMenu.setCursor(74, 8);
	displayMenu.print("Tiré:");
	displayMenu.print(bbtire);

	displayMenu.setCursor(0, 32);
	displayMenu.print(modeValue);

	displayMenu.setCursor(64,32);
	displayMenu.print("Volts:");
	displayMenu.print(voltValue);
 displayMenu.sendBuffer();
}

void Menu::MenuFullBurst(int8_t ROFFull, int8_t ROFBurst, int8_t BurstBB, int8_t sousMenuValue)
{
  displayMenu.clearBuffer();
	displayMenu.setCursor(0, 8);
	displayMenu.print("ROF Full:");
	displayMenu.print(ROFFull);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("ROF Burst:");
	displayMenu.print(ROFBurst);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}

	displayMenu.setCursor(74,32);
	if (sousMenuValue == 2)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(80, 32);
	displayMenu.print("Qte BB:");
	displayMenu.print(BurstBB);
 displayMenu.sendBuffer();
}

void Menu::MenuSniper(int8_t timeBolt, bool greenLed, int8_t sousMenuValue)
{
	displayMenu.clearBuffer();

	//
	displayMenu.setCursor(0, 8);
	displayMenu.print("LED Vert ?:");
	displayMenu.print(greenLed);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("Interv.:");
	displayMenu.print(timeBolt);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}
 displayMenu.sendBuffer();
}

void Menu::MenuChargeur1(int16_t chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int8_t sousMenuValue)
{
	displayMenu.clearBuffer();

	//
	displayMenu.setCursor(0, 8);
	displayMenu.print("Cap:");
	displayMenu.print(chargeurCap);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(66, 8);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(72, 8);
	displayMenu.print("Bloc ?:");
	displayMenu.print(blocage);

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("Charg ?:");
	displayMenu.print(switchchargeur);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(66, 32);
	if (sousMenuValue == 3)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(72, 32);
	displayMenu.print("Buzz ?:");
	displayMenu.print(buzzer);

  displayMenu.sendBuffer();
}

void Menu::MenuChargeur2(bool alarm, int8_t alarmLowBB, bool chargingHandle, bool greenLight, int8_t sousMenuValue)
{
	displayMenu.clearBuffer();

	//
	displayMenu.setCursor(0, 8);
	displayMenu.print("Alarm ?:");
	displayMenu.print(alarm);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 8);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 8);
	displayMenu.print("Qte:");
	displayMenu.print(alarmLowBB);

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("Hand ?:");
	displayMenu.print(chargingHandle);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 32);
	if (sousMenuValue == 3)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 32);
	displayMenu.print("LED ?:");
	displayMenu.print(greenLight);
displayMenu.sendBuffer();
}

void Menu::MenuSetting(int8_t veille, bool verrou, bool LowBat, int8_t sousMenuValue)
{
	displayMenu.clearBuffer();
	
	//
	displayMenu.setCursor(0, 8);
	displayMenu.print("Ver ?:");
	displayMenu.print(verrou);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 8);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 8);
	displayMenu.print("Time:");
	displayMenu.print(veille);

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("Al Bat ?:");
	displayMenu.print(LowBat);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}
 displayMenu.sendBuffer();
}

void Menu::MenuSetting2(int8_t semi, int8_t full, int16_t dwel, int8_t sousMenuValue)
{
	displayMenu.clearBuffer();

	//
	displayMenu.setCursor(0, 8);
	displayMenu.print("Semi:");
	displayMenu.print(semi);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 32);
	displayMenu.print("Full:");
	displayMenu.print(full);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(64, 32);
	if (sousMenuValue == 2)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(70, 32);
	displayMenu.print("DWEL:");
	displayMenu.print(dwel);
displayMenu.sendBuffer();
}

void Menu::MenuDever()
{
	displayMenu.clearBuffer();

	displayMenu.setCursor(0, 12);
	displayMenu.print("Deverrouillage !");

	displayMenu.sendBuffer();
}

void Menu::MenuVer()
{
	displayMenu.clearBuffer();

	displayMenu.setCursor(0, 12);
	displayMenu.print("Verrouillage !");

  displayMenu.sendBuffer();

}
