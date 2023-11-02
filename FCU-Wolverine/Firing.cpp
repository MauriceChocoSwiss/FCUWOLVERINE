#include "Firing.h"

Firing::Firing() {

}

void Firing::Fire(uint8_t pin, uint16_t dwel)
{
    digitalWrite(pin, 1);
    delay(dwel / 2.5);
    digitalWrite(pin, 0);
}
