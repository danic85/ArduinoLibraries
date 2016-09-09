#ifndef CD74HC4067_h
#define CD74HC4067_h

#include "Arduino.h"

#define MUX_S0 7
#define MUX_S1 6
#define MUX_S2 5
#define MUX_S3 4
#define MUX_SIG A0

class CD74HC4067
{
  public:
    CD74HC4067(int enablePin);
    int readChannel(int channel);
    int nextChannel();
  private:
    int _lastChannel;
    int _enablePin;
};

#endif
