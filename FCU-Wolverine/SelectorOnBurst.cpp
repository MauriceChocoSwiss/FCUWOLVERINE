// 
// 
// 
#include <Arduino.h>
#include "SelectorOnBurst.h"

SelectorOnBurst::SelectorOnBurst()
{
}

bool SelectorOnBurst::selectorBurst(int pin, int dwel, int rof, int repeat)
{
  Serial.println(repeat);
    for (int x = 1; x <= repeat; x++) {

        digitalWrite(pin, 1);

        delay(dwel /2.5);

        digitalWrite(pin, 0);

        delay(1000 / rof);

        Serial.println("fire");
    }

	return true;
}
