#include "Arduino.h"
#include "CD74HC4067.h"

int controlPin[] = {MUX_S0, MUX_S1, MUX_S2, MUX_S3};

int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};

CD74HC4067::CD74HC4067(int enablePin)
{
    pinMode( MUX_S0, OUTPUT );
    pinMode( MUX_S1, OUTPUT );
    pinMode( MUX_S2, OUTPUT );
    pinMode( MUX_S3, OUTPUT );
    pinMode( MUX_SIG, INPUT );
    pinMode( enablePin, OUTPUT );

    digitalWrite(MUX_S0, LOW);
    digitalWrite(MUX_S1, LOW);
    digitalWrite(MUX_S2, LOW);
    digitalWrite(MUX_S3, LOW);
    digitalWrite(enablePin, LOW); // enable
    
    _enablePin = enablePin;
    _lastChannel = -1;
}
int CD74HC4067::readChannel(int channel)
{
  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  _lastChannel = channel;

  //read the value at the SIG pin
  int val = analogRead(MUX_SIG);

  // Loop if no value (end of thread)
  if (val == 0)
  {
    return readChannel(0);
  }

  //return the value
  return val;
}

int CD74HC4067::nextChannel()
{
  int channel = _lastChannel +1;
  if (channel > 15)
  {
    channel = 0;
  }
  return channel;
}

