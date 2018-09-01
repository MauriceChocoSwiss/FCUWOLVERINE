#include "armed.h"


Armed::Armed() {

}

void Armed::armed(int pin) {
	digitalWrite(pin, 1);
	delay(10);
	digitalWrite(pin, 0);
	delay(800);
}