//#define SHELL_READ_PIN 0
#define READING_TOLERANCE 5

#define SHELL_ITERATION_DELAY 1000

#include "HG7881.h"
#include "Lights.h"
#include "CD74HC4067.h"
#include "HCSR04.h"

// Initialise Modules
HG7881 motors;
Lights lights;
CD74HC4067 mux1(A1);
HCSR04 sensor;

void setup() 
{
//  pinMode(SHELL_READ_PIN, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  delay(SHELL_ITERATION_DELAY);

  long distance = sensor.doPing();
  Serial.print("Sensor distance: ");
  Serial.println(distance);

  // Read value of next multiplexer channel
  int channel = mux1.nextChannel();
  Serial.print("Reading channel: ");
  Serial.println(channel);
  int value = mux1.readChannel(channel);
  Serial.println(value);
  
  int lightActions[] = {LIGHT_ON, LIGHT_OFF};
  int motorActions[] = {DIRECTION_FORWARDS, DIRECTION_BACKWARDS, DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_STOP};

  int motorAction = getMatch(value, motorActions,  (int)( sizeof(motorActions) / sizeof(motorActions[0])));
  if (motorAction > -1) motors.doAction(motorAction);
  else 
  {
    int lightAction = getMatch(value, lightActions,  (int)( sizeof(lightActions) / sizeof(lightActions[0])));
    if (lightAction > -1) lights.doAction(lightAction);
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
int getMatch (int value, int *actions, int len)
{
    for (int i; i < len; i++)
    {
        bool match = isMatch(value, actions[i]);
        if (match) return actions[i];
    }
    return -1;
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
