//DelayTimer.h

#ifndef _DELAYTIMER_h
#define _DELAYTIMER_h
#include "Arduino.h"

class DelayTimer {
public:
  DelayTimer();
  DelayTimer(unsigned long interval);

  bool isTimeReached(unsigned long currentTime, unsigned long interval);
  bool isTimeReached(unsigned long currentTime);
  bool isTimeReached() {
    return isTimeReached(millis());
  };
  bool isTimeReachedAutoReset(unsigned long currentTime, unsigned long interval);
  bool isTimeReachedAutoReset(unsigned long currentTime);
  
  void setLastTime(unsigned long time) {
    this->_lastTime = time;
  };

  void setInterval(unsigned long interval) {
    this->_interval = interval;
  };

  void Reset() {
    setLastTime(millis());
  };

private:
  unsigned long _lastTime = 0;
  unsigned long _interval = 0;
};

#endif
