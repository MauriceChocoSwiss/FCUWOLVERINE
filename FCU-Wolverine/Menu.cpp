//#include <U8x8lib.h>
#include <U8g2lib.h>
#include "Menu.h"
#include <Wire.h>

//U8X8_SSD1306_128X32_UNIVISION_HW_I2C displayMenu(U8X8_PIN_NONE, A5, A4);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C displayMenu(U8G2_R2);

Menu::Menu() {
}

void Menu::StartMenu(uint8_t buzzer) {
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

void Menu::MainMenu(double voltValue, uint16_t bbsLeft, uint16_t bbsLeftMag, String modeValue, uint16_t bbsShot) {
  displayMenu.clearBuffer();
  displayMenu.setCursor(0, 8);
  displayMenu.print("BB:");
  displayMenu.print(bbsLeft);
  displayMenu.print("|");
  displayMenu.print(bbsLeftMag);
  displayMenu.setCursor(74, 8);
  displayMenu.print("Tiré:");
  displayMenu.print(bbsShot);

  displayMenu.setCursor(0, 32);
  displayMenu.print(modeValue);

  displayMenu.setCursor(64, 32);
  displayMenu.print("Volts:");
  displayMenu.print(voltValue);
  displayMenu.sendBuffer();
}

void Menu::FullBurstMenu(uint8_t ROFFull, uint8_t ROFBurst, uint8_t BurstBB, uint8_t subMenuValue) {
  displayMenu.clearBuffer();
  displayMenu.setCursor(0, 8);
  displayMenu.print("ROF Full:");
  displayMenu.print(ROFFull);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("ROF Burst:");
  displayMenu.print(ROFBurst);
  if (subMenuValue == 1) {
    displayMenu.print("<");
  }

  displayMenu.setCursor(74, 32);
  if (subMenuValue == 2) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(80, 32);
  displayMenu.print("Qty BB:");
  displayMenu.print(BurstBB);
  displayMenu.sendBuffer();
}

void Menu::SniperMenu(uint8_t timeBolt, bool greenLed, uint8_t subMenuValue) {
  displayMenu.clearBuffer();

  //
  displayMenu.setCursor(0, 8);
  displayMenu.print("Green LED ?:");
  displayMenu.print(greenLed);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("Timing.:");
  displayMenu.print(timeBolt);
  if (subMenuValue == 1) {
    displayMenu.print("<");
  }
  displayMenu.sendBuffer();
}

void Menu::MagMenu1(uint16_t magCapacity, bool magSwitch, bool buzzer, bool emptyMagBlocking, uint8_t subMenuValue) {
  displayMenu.clearBuffer();

  //
  displayMenu.setCursor(0, 8);
  displayMenu.print("Cap:");
  displayMenu.print(magCapacity);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(66, 8);
  if (subMenuValue == 1) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(72, 8);
  displayMenu.print("Block ?:");
  displayMenu.print(emptyMagBlocking);

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("Mag ?:");
  displayMenu.print(magSwitch);
  if (subMenuValue == 2) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(66, 32);
  if (subMenuValue == 3) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(72, 32);
  displayMenu.print("Buzz ?:");
  displayMenu.print(buzzer);

  displayMenu.sendBuffer();
}

void Menu::MagMenu2(bool alarm, uint8_t alarmLowBB, bool chargingHandle, bool greenLight, uint8_t subMenuValue) {
  displayMenu.clearBuffer();

  //
  displayMenu.setCursor(0, 8);
  displayMenu.print("Alarm ?:");
  displayMenu.print(alarm);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(70, 8);
  if (subMenuValue == 1) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(76, 8);
  displayMenu.print("Qty:");
  displayMenu.print(alarmLowBB);

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("Hand ?:");
  displayMenu.print(chargingHandle);
  if (subMenuValue == 2) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(70, 32);
  if (subMenuValue == 3) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(76, 32);
  displayMenu.print("LED ?:");
  displayMenu.print(greenLight);
  displayMenu.sendBuffer();
}

void Menu::SettingsMenu1(uint8_t screenLockValue, bool screenLockOption, bool LowBat, uint8_t subMenuValue) {
  displayMenu.clearBuffer();

  //
  displayMenu.setCursor(0, 8);
  displayMenu.print("Ver ?:");
  displayMenu.print(screenLockOption);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(70, 8);
  if (subMenuValue == 1) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(76, 8);
  displayMenu.print("Timer:");
  displayMenu.print(screenLockValue);

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("Al Bat ?:");
  displayMenu.print(LowBat);
  if (subMenuValue == 2) {
    displayMenu.print("<");
  }
  displayMenu.sendBuffer();
}

void Menu::SettingMenu2(uint8_t semi, uint8_t full, uint16_t dwel, uint8_t subMenuValue) {
  displayMenu.clearBuffer();

  //
  displayMenu.setCursor(0, 8);
  displayMenu.print("Semi:");
  displayMenu.print(semi);
  if (subMenuValue == 0) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(0, 32);
  displayMenu.print("Full:");
  displayMenu.print(full);
  if (subMenuValue == 1) {
    displayMenu.print("<");
  }

  //
  displayMenu.setCursor(64, 32);
  if (subMenuValue == 2) {
    displayMenu.print(">");
  }
  displayMenu.setCursor(70, 32);
  displayMenu.print("DWEL:");
  displayMenu.print(dwel);
  displayMenu.sendBuffer();
}

void Menu::UnlockDisplay() {
  displayMenu.clearBuffer();

  displayMenu.setCursor(0, 12);
  displayMenu.print("Unlocking !");

  displayMenu.sendBuffer();
}

void Menu::lockDisplay() {
  displayMenu.clearBuffer();

  displayMenu.setCursor(0, 12);
  displayMenu.print("Locking !");

  displayMenu.sendBuffer();
}
