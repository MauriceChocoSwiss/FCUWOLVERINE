// 
// 
// 

#include <Arduino.h>
#include "SelectorOnSemi.h"


SelectorOnSemi::SelectorOnSemi() {
}

void SelectorOnSemi::selectorSemi(int pin, int dwel)
{
      float dwelUpdate = dwel / 2.5;
      digitalWrite(pin, 1);
      delay(dwelUpdate);
      digitalWrite(pin, 0);  
}
