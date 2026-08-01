#include "Alarm.h"

#include "Menu.h"
#include "VoltageCtrl.h"
#include "Firing.h"
#include <EEPROM.h>
#include "DelayTimer.h"

//pin assignment
uint8_t trigger = 3;
uint8_t selector = 2;
uint8_t magazine = 4;
uint8_t reloadLEDRed = 5;
uint8_t reloadLEDGreen = 6;
uint8_t reloadLEDBlue = 7;
uint8_t solenoid = 8;
uint8_t buzzer = 13;

uint8_t joyBottom = 12;
uint8_t joyLeft = 11;
uint8_t joyUp = 10;
uint8_t joyRight = 9;
uint8_t joyCenter = A0;
uint8_t chargingHandle = A7;
uint8_t batteryReading = A1;

//set switch states to 0
int16_t triggerSwitch = 0;
int16_t selectorSwitch = 0;
int16_t magSwitch = 0;
int16_t handleSwitch = 0;
int16_t joyBottomPush = 0;
int16_t joyLeftPush = 0;
int16_t joyUpPush = 0;
int16_t joyRightPush = 0;
int16_t joyCenterPush = 0;

//local variables
int16_t bbsLeftMagValue;
int16_t bbsLeft;
uint8_t alarmBB;
uint8_t ROFFull;
uint8_t ROFBurst;
uint8_t burstBB;
uint8_t semiMode;
uint8_t fullMode;
uint8_t timeBolt;
uint16_t delayBolt;
uint16_t dwel;
unsigned long firstCenterPushed;
String modeValue;
uint8_t menuValue = 0;
uint8_t subMenuValue = 0;
bool paramValuePlus = false;
bool paramValueMoins = false;
uint16_t bbsFired = 0;
unsigned long previousMillisBolt = 0;
unsigned long currentTime;
uint8_t fivePressCount = 0;

//Delay
DelayTimer firingTimer;

//options
bool magOption;
bool handleOption;
bool buzzOption;
bool emptyMagLockOption;
bool alarmBBOption;
bool screenLockOption;
bool SnipeReadyLEDOPtion;
bool greenLightChargingHandleOption;
bool alarmBatOption;

//states
bool triggerStateFired = false;
bool sniperBlocked = false;
bool magState = false;
bool emptyMagBlockingState = false;
bool alarmLowPassed = false;
bool alarmEmptyPassed = false;
bool editMode = false;
bool saveEdit = false;
bool alarmBatLow = false;
bool programingMode = false;
bool fivePressBlocked = false;

//Eeprom Addresses
uint8_t ROFFullAdress = 0;            //2
uint8_t ROFBurstAdress = 2;           //2
uint8_t burstBBAdress = 4;            //2
uint8_t SnipeReadyAdress = 6;         //1
uint8_t timeBoltAdress = 7;           //2
uint8_t bbrestAdress = 9;             //3
uint8_t magOptionAdress = 12;         //1
uint8_t buzzOptionAdress = 13;        //1
uint8_t emptyMagLockingAdress = 14;   //1
uint8_t alarmBBOptionAdress = 15;     //1
uint8_t alarmBBAdress = 16;           //2
uint8_t handleOptionAdress = 18;      //1
uint8_t greenLightHandleAdress = 19;  //1
uint8_t screenLockTimerAdress = 20;   //3
uint8_t dwelAdress = 23;              //3
uint8_t screenLockOptionAdress = 26;  //1
uint8_t alarmBatAdress = 27;          //1
uint8_t semiModeAdress = 28;          //2
uint8_t fullModeAdress = 30;          //


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
  pinMode(joyCenter, INPUT);
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
  EEPROM.get(magOptionAdress, magOption);
  EEPROM.get(handleOptionAdress, handleOption);
  EEPROM.get(buzzOptionAdress, buzzOption);
  EEPROM.get(emptyMagLockingAdress, emptyMagLockOption);
  EEPROM.get(alarmBBOptionAdress, alarmBBOption);
  EEPROM.get(SnipeReadyAdress, SnipeReadyLEDOPtion);
  EEPROM.get(greenLightHandleAdress, greenLightChargingHandleOption);
  EEPROM.get(alarmBatAdress, alarmBatOption);

  menu.StartMenu(buzzer);
}

void loop() {
shoot:  //step to by-pass non essentials functions
  currentTime = millis();
  double voltValue = voltCtrl.VoltageValue(batteryReading);

  triggerSwitch = digitalRead(trigger);
  selectorSwitch = digitalRead(selector);
  magSwitch = digitalRead(magazine);
  handleSwitch = analogRead(chargingHandle);
  joyBottomPush = digitalRead(joyBottom);
  joyRightPush = digitalRead(joyRight);
  joyLeftPush = digitalRead(joyLeft);
  joyUpPush = digitalRead(joyUp);
  joyCenterPush = digitalRead(joyCenter);

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
  if (triggerSwitch == HIGH && !triggerStateFired && magState && !emptyMagBlockingState && !alarmBatLow) {
    uint8_t x = 0;
    switch (selectorSwitch == HIGH ? fullMode : semiMode) {
      case 1:
        firing.Fire(solenoid, dwel);

        bbsLeft -= 1;
        bbsFired += 1;

        triggerStateFired = true;
        break;
      case 2:
        while (x != burstBB) {
          if (firingTimer.isTimeReachedAutoReset(millis(), (1000 / ROFBurst))) {
            firing.Fire(solenoid, dwel);
            x++;
          }
        }

        bbsLeft -= burstBB;
        bbsFired += burstBB;
        triggerStateFired = true;
        break;
      case 3:
        if (firingTimer.isTimeReachedAutoReset(currentTime, (1000 / ROFFull))) {
          firing.Fire(solenoid, dwel);
          bbsLeft -= 1;
          bbsFired += 1;
        }
        break;
      case 4:
        Serial.println("zob");
        if (!sniperBlocked) {
          firing.Fire(solenoid, dwel);

          bbsLeft -= 1;
          bbsFired += 1;

          previousMillisBolt = currentTime;
        }

        triggerStateFired = true;
        sniperBlocked = true;
        delayBolt = timeBolt * 250;
        break;
    }
    menuValue = 0;
  }

  //reset sniper after firing
  if (currentTime - previousMillisBolt >= delayBolt && sniperBlocked) {
    sniperBlocked = false;

    if (SnipeReadyLEDOPtion) {
      digitalWrite(reloadLEDGreen, 1);
      delay(10);
      digitalWrite(reloadLEDGreen, 0);
    }
  }

  //Fire blocking when semi
  if (triggerSwitch == LOW && triggerStateFired) {
    triggerStateFired = false;
  }

  //Magazine Option
  if (magOption) {
    if (magSwitch == HIGH) {
      magState = true;
    } else {
      magState = false;
    }
  } else {
    magState = true;
  }

  //Empty mag option
  if (emptyMagLockOption && bbsLeft <= 0) {
    emptyMagBlockingState = true;
  }

  //BB's alarm
  if (alarmBBOption) {
    //"Empty BB's" Alarm
    if (bbsLeft <= 0 && alarmEmptyPassed == false) {
      alarmEmptyPassed = alarm.AlarmEmpty(reloadLEDRed);

      if (buzzOption == true) {
        alarm.BuzzerLow(buzzer);
      }
    }

    //"Near Empty" bb's alarm
    if (bbsLeft <= alarmBB && alarmLowPassed == false) {
      alarmLowPassed = alarm.AlarmLowBB(reloadLEDBlue);
    }
  }

  //check trigger to by-pass if we are not in programming mode
  if (triggerSwitch == HIGH && !programingMode) {
    goto shoot;  //by-passing
  }

  //Battery Voltage Alarm
  if (alarmBatOption) {
    if (voltCtrl.alarmVoltage(voltValue, currentTime)) {
      alarm.AlarmBat(reloadLEDRed);

      alarmBatLow = true;

      if (buzzOption == true) {
        alarm.BuzzerBat(buzzer);
      }
    }
  }

  //Charging Handle Option
  if (handleOption) {
    if (handleSwitch >= 1010) {
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

  //Reading joystick
  if (programingMode) {
    if (joyBottomPush == HIGH) {
      digitalWrite(reloadLEDBlue, 1);  //Lighting Green
      digitalWrite(reloadLEDRed, 1);   //Lighting Green

      if (editMode) {
        paramValueMoins = true;
        delay(50);
      } else {
        subMenuValue = 0;

        if (menuValue == 0) {
          menuValue = 5;
        } else {
          menuValue = menuValue - 1;
        }
        delay(200);
      }
      digitalWrite(reloadLEDBlue, 0);  //Delighting green
      digitalWrite(reloadLEDRed, 0);   //Delighting green
    }

    if (joyUpPush == HIGH) {
      digitalWrite(reloadLEDBlue, 1);  //Lighting Green
      digitalWrite(reloadLEDRed, 1);   //Lighting Green

      if (editMode) {
        paramValuePlus = true;
        delay(50);
      } else {
        subMenuValue = 0;

        if (menuValue == 5) {
          menuValue = 0;
        } else {
          menuValue = menuValue + 1;
        }
        delay(200);
      }

      digitalWrite(reloadLEDBlue, 0);  //Delighting green
      digitalWrite(reloadLEDRed, 0);   //Delighting green
    }

    if (joyRightPush == HIGH && editMode == false) {
      digitalWrite(reloadLEDBlue, 1);  //Lighting Green
      digitalWrite(reloadLEDRed, 1);   //Lighting Green

      if (subMenuValue < 3) {
        subMenuValue = subMenuValue + 1;
      }

      delay(200);
      digitalWrite(reloadLEDBlue, 0);  //Delighting green
      digitalWrite(reloadLEDRed, 0);   //Delighting green
    }

    if (joyLeftPush == HIGH && editMode == false) {
      digitalWrite(reloadLEDBlue, 1);  //Lighting Green
      digitalWrite(reloadLEDRed, 1);   //Lighting Green

      if (subMenuValue > 0) {
        subMenuValue = subMenuValue - 1;
      }

      delay(200);
      digitalWrite(reloadLEDBlue, 0);  //Delighting green
      digitalWrite(reloadLEDRed, 0);   //Delighting green
    }
  }

  //Center button
  if (joyCenterPush) {
    digitalWrite(reloadLEDBlue, 1);  //Lighting Green
    digitalWrite(reloadLEDRed, 1);   //Lighting Green

    //enter or save edition
    if (editMode) {
      editMode = false;
      saveEdit = true;
    } else if (editMode == false) {
      editMode = true;
      saveEdit = false;
    }

    delay(50);
    digitalWrite(reloadLEDBlue, 0);  //Delighting green
    digitalWrite(reloadLEDRed, 0);   //Delighting green

    //if we haven't pushed the center button from last 1s, we reset the counter and restart multipress
    if (firstCenterPushed < currentTime - 1000) {
      fivePressCount = 1;
      firstCenterPushed = currentTime;
      fivePressBlocked = true;
    }

    if (!fivePressBlocked) {
      fivePressCount++;
      fivePressBlocked = true;
    }

    //if we hit 5 times in 1s the center button, we enter/left programming mode
    if (fivePressCount >= 5) {
      fivePressCount = 0;
      programingMode = !programingMode;
      if (programingMode) {
        menu.EnterProgMode();
      } else {
        menu.SettingsSaved();
      }
      delay(500);
    }
  } else {
    fivePressBlocked = false;
  }

  //Menu's
  if (programingMode) {
    switch (menuValue) {
      case 0:
        menu.FullBurstMenu(ROFFull, ROFBurst, burstBB, subMenuValue);

        if (subMenuValue == 0) {
          ROFFull = savingToEEPROM(ROFFullAdress, ROFFull, 1, 44);
        }

        if (subMenuValue == 1) {
          ROFBurst = savingToEEPROM(ROFBurstAdress, ROFBurst, 1, 44);
        }

        if (subMenuValue == 2) {
          burstBB = savingToEEPROM(burstBBAdress, burstBB, 1, 20);
        }

        break;
      case 1:
        menu.SniperMenu(timeBolt, SnipeReadyLEDOPtion, subMenuValue);

        if (subMenuValue == 0) {
          SnipeReadyLEDOPtion = savingToEEPROM(SnipeReadyAdress, SnipeReadyLEDOPtion);
        }

        if (subMenuValue == 1) {
          timeBolt = savingToEEPROM(timeBoltAdress, timeBolt, 2, 9);
        }

        break;
      case 2:
        menu.MagMenu1(bbsLeftMagValue, magOption, buzzOption, emptyMagLockOption, subMenuValue);

        if (subMenuValue == 0) {
          bbsLeftMagValue = savingToEEPROM(bbrestAdress, bbsLeftMagValue, 1, 1999);
        }

        if (subMenuValue == 1) {
          emptyMagLockOption = savingToEEPROM(emptyMagLockingAdress, emptyMagLockOption);
        }

        if (subMenuValue == 2) {
          magOption = savingToEEPROM(magOptionAdress, magOption);
        }

        if (subMenuValue == 3) {
          buzzOption = savingToEEPROM(buzzOptionAdress, buzzOption);
        }

        break;
      case 3:
        menu.MagMenu2(alarmBBOption, alarmBB, handleOption, greenLightChargingHandleOption, subMenuValue);

        if (subMenuValue == 0) {
          alarmBBOption = savingToEEPROM(alarmBBOptionAdress, alarmBBOption);
        }

        if (subMenuValue == 1) {
          alarmBB = savingToEEPROM(alarmBBAdress, alarmBB, 1, 19);
        }

        if (subMenuValue == 2) {
          handleOption = savingToEEPROM(handleOptionAdress, handleOption);
        }

        if (subMenuValue == 3) {
          greenLightChargingHandleOption = savingToEEPROM(greenLightHandleAdress, greenLightChargingHandleOption);
        }

        break;
      case 4:
        menu.SettingMenu(semiMode, fullMode, dwel, alarmBatOption, subMenuValue);

        if (subMenuValue == 0) {
          semiMode = savingToEEPROM(semiModeAdress, semiMode, 2, 3);
        }

        if (subMenuValue == 1) {
          fullMode = savingToEEPROM(fullModeAdress, fullMode, 2, 3);
        }

        if (subMenuValue == 2) {
          dwel = savingToEEPROM(dwelAdress, dwel, 0, 2999);
        }

        if (subMenuValue == 3) {
          alarmBatOption = savingToEEPROM(alarmBatAdress, alarmBatOption);
        }
        break;
    }
  } else {
    menu.MainMenu(voltValue, bbsLeft, bbsLeftMagValue, modeValue, bbsFired);
  }

  paramValueMoins = false;
  paramValuePlus = false;
}

int16_t savingToEEPROM(uint8_t eepromAddress, int16_t parameter, int16_t minValue, int16_t maxValue) {
  if (editMode) {
    //Value modifying
    if (paramValueMoins && parameter >= minValue) {
      parameter -= 1;
    } else if (paramValuePlus && parameter <= maxValue) {
      parameter += 1;
    }
  }

  if (saveEdit) {
    //Saving in EEPROM
    EEPROM.put(eepromAddress, parameter);
    saveEdit = false;
  }
  return parameter;
}

bool savingToEEPROM(uint8_t eepromAddress, bool parameter) {
  if (editMode) {
    //Value modifying
    if (paramValueMoins && parameter) {
      parameter = false;
    } else if (paramValuePlus && !parameter) {
      parameter = true;
    }
  }

  if (saveEdit) {
    //Saving in EEPROM
    EEPROM.put(eepromAddress, parameter);
    saveEdit = false;
  }
  return parameter;
}
