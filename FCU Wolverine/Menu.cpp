#include "Menu.h"
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 displayMenu;



Menu::Menu() {
}

void Menu::StartMenu(int buzzer) {
	displayMenu.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64) 
													
	// draw a single pixel // Dessine un pixel blanc aux coordonnées 10,10

	//display.drawPixel(10, 10, WHITE);
	//display.display();
	//delay(2000);
	displayMenu.clearDisplay();

	// text display tests
	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);
	displayMenu.setCursor(20, 12);
	displayMenu.print("Hello Soldier !");
	displayMenu.display();
	delay(3000);
	displayMenu.clearDisplay();


	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);
	displayMenu.setCursor(30, 12);
	displayMenu.print("Let's Play !");
	displayMenu.display();
	delay(1000);
	tone(buzzer, 2000, 500);
	delay(1000);
	noTone(buzzer);
	displayMenu.clearDisplay();

}

void Menu::MainDisplay(double voltValue, int bbrest, int bbrestChargeur, String modeValue, int bbtire)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	displayMenu.setCursor(0, 0);
	displayMenu.print("BB:");
	displayMenu.print(bbrest);
	displayMenu.print("|");
	displayMenu.print(bbrestChargeur);
	displayMenu.setCursor(74, 0);
	displayMenu.print("Tire:");
	displayMenu.print(bbtire);

	displayMenu.setCursor(0, 24);
	displayMenu.print(modeValue);

	displayMenu.setCursor(60, 24);
	displayMenu.print("Volts:");
	displayMenu.print(voltValue);

	displayMenu.display();
}


void Menu::MenuFullBurst(int ROFFull, int ROFBurst, int QteBB,int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("ROF FULL:");
	displayMenu.print(ROFFull);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("ROF BURST:");
	displayMenu.print(ROFBurst);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(74, 24);
	if (sousMenuValue == 2)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(80, 24);
	displayMenu.print("Qte BB:");
	displayMenu.print(QteBB);

	displayMenu.display();

}

void Menu::MenuSniper(int timeBolt, bool greenLed, int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("LED Vert ?:");
	displayMenu.print(greenLed);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("Interv.:");
	displayMenu.print(timeBolt);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}

	displayMenu.display();

}

void Menu::MenuChargeur1(int chargeurCap, bool switchchargeur, bool buzzer, bool blocage, int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("Cap:");
	displayMenu.print(chargeurCap);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(66, 0);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(72, 0);
	displayMenu.print("Bloc ?:");
	displayMenu.print(blocage);

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("Charg ?:");
	displayMenu.print(switchchargeur);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(66, 24);
	if (sousMenuValue == 3)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(72, 24);
	displayMenu.print("Buzz ?:");
	displayMenu.print(buzzer);

	displayMenu.display();

}

void Menu::MenuChargeur2(bool alarm, int alarmLowBB, bool chargingHandle, bool greenLight, int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("Alarm ?:");
	displayMenu.print(alarm);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 0);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 0);
	displayMenu.print("Qte:");
	displayMenu.print(alarmLowBB);

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("Hand ?:");
	displayMenu.print(chargingHandle);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 24);
	if (sousMenuValue == 3)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 24);
	displayMenu.print("LED ?:");
	displayMenu.print(greenLight);

	displayMenu.display();

}

void Menu::MenuSetting(int veille, bool verrou, bool LowBat, int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);
	
	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("Ver ?:");
	displayMenu.print(verrou);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(70, 0);
	if (sousMenuValue == 1)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(76, 0);
	displayMenu.print("Time:");
	displayMenu.print(veille);

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("Al Bat ?:");
	displayMenu.print(LowBat);
	if (sousMenuValue == 2)
	{
		displayMenu.print("<");
	}

	displayMenu.display();

}

void Menu::MenuSetting2(int semi, int full, int dwel, int sousMenuValue)
{
	displayMenu.clearDisplay();

	displayMenu.setTextSize(1);
	displayMenu.setTextColor(WHITE);

	//
	displayMenu.setCursor(0, 0);
	displayMenu.print("Semi:");
	displayMenu.print(semi);
	if (sousMenuValue == 0)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(0, 24);
	displayMenu.print("Full:");
	displayMenu.print(full);
	if (sousMenuValue == 1)
	{
		displayMenu.print("<");
	}

	//
	displayMenu.setCursor(64, 24);
	if (sousMenuValue == 2)
	{
		displayMenu.print(">");
	}
	displayMenu.setCursor(70, 24);
	displayMenu.print("DWEL:");
	displayMenu.print(dwel);


	displayMenu.display();
}