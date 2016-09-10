#ifndef HCSR04_h
#define HCSR04_h

#include "Arduino.h"

#define TRIGGER_PIN A3
#define ECHO_PIN A2

class HCSR04
{
  public:
    HCSR04();
    long doPing();
    long microsecondsToInches(long microseconds);
};

#endif
