//
//
//

#include "DelayTimer.h"

DelayTimer::DelayTimer(){};

DelayTimer::DelayTimer(unsigned long interval) {
  setInterval(interval);
}

bool DelayTimer::isTimeReached(unsigned long currentTime) {
  return isTimeReached(currentTime, this->_interval);
}

bool DelayTimer::isTimeReached(unsigned long currentTime, unsigned long interval) {
  if (currentTime > _lastTime + interval) {
    return true;
  }
  return false;
}

bool DelayTimer::isTimeReachedAutoReset(unsigned long currentTime) {
  return isTimeReachedAutoReset(currentTime, this->_interval);
}

bool DelayTimer::isTimeReachedAutoReset(unsigned long currentTime, unsigned long interval) {
  if (currentTime > _lastTime + interval) {
    _lastTime = currentTime;

    return true;
  }
  return false;
}
