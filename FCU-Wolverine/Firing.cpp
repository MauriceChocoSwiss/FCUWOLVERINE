#include "Firing.h"

Firing::Firing() {

}

void Firing::Fire(int8_t pin, int16_t dwel)
{
    digitalWrite(pin, 1);
    delay(dwel / 2.5);
    digitalWrite(pin, 0);
}
