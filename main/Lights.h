#ifndef Lights_h
#define Lights_h

#include "Arduino.h"

#define LIGHT_PIN 12

#define LIGHT_ON 62
#define LIGHT_OFF 91

class Lights
{
  public:
    Lights();
    void doAction(int action);
  private:
    int _lastAction;
};

#endif
