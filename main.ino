//#define SHELL_READ_PIN 0
#define READING_TOLERANCE 4

#define SHELL_ITERATION_DELAY 1000

#include "HG7881.h"
#include "Lights.h"
#include "CD74HC4067.h"

// Initialise Modules
HG7881 motors;
Lights lights;
CD74HC4067 mux1(A1);

void setup() 
{
//  pinMode(SHELL_READ_PIN, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  delay(SHELL_ITERATION_DELAY);

  // Read value of next multiplexer channel
  int value = mux1.readChannel(mux1.nextChannel());
  Serial.println(value);
  
  //@todo implement array checking.
  int lightActions[] = {LIGHT_ON, LIGHT_OFF};
  int motorActions[] = {DIRECTION_FORWARDS, DIRECTION_BACKWARDS, DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_STOP};
  if (isMatch(value, motorActions,  (int)( sizeof(motorActions) / sizeof(motorActions[0])))) motors.doAction(value);
  else if (isMatch(value, lightActions,(int)( sizeof(motorActions) / sizeof(motorActions[0])))) lights.doAction(value);
  else
  {
    pr("Loop");
  } 
}

/*
 * Action matches given value
 */
bool isMatch (int value, int action)
{
    return (value < action + READING_TOLERANCE && value > action - READING_TOLERANCE);
}

/*
 * Action matches one in array
 */
bool isMatch (int value, int *actions, int len)
{
    for (int i; i < len; i++)
    {
        Serial.print("Checking: ");
        Serial.println(actions[i]);
        if (isMatch(value, actions[i])) return true;
    }
    return false;
}

/*
 * Serial Print String
 */
void pr(const char* str)
{
  Serial.println(str);
}

/*
 * Reset all to initial values
 */
void restart()
{
  lights.doAction(LIGHT_OFF);
  motors.doAction(DIRECTION_STOP);
}
