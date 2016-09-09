#ifndef HG7881_h
#define HG7881_h

#include "Arduino.h"

// wired connections
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 11 // D11 --> Motor B Input B --> MOTOR B -
#define HG7881_A_IA 9 // D9 --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 8 // D8 --> Motor A Input B --> MOTOR A -

// functional connections
#define MOTOR_R_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_R_DIR HG7881_B_IB // Motor B Direction
#define MOTOR_L_PWM HG7881_A_IA // Motor A PWM Speed
#define MOTOR_L_DIR HG7881_A_IB // Motor A Direction

#define MOTOR_DELAY 1000 // brief delay for abrupt motor changes

#define DIRECTION_STOP 0
#define DIRECTION_FORWARDS 991
#define DIRECTION_BACKWARDS 985
#define DIRECTION_LEFT 236
#define DIRECTION_RIGHT 1018

#define MOTOR_FORWARD HIGH
#define MOTOR_FORWARD_SPEED 50
#define MOTOR_REVERSE LOW
#define MOTOR_REVERSE_SPEED 230 //@todo why does this need to be higher than forward speed?


class HG7881
{
  public:
    HG7881();
    void doAction(int direction);
    void stop();
    void stop(bool wait);
  private:
    int _lastAction;
};

#endif
