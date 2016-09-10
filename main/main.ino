#define READING_TOLERANCE 5

#define SHELL_ITERATION_DELAY 1000

#include "HG7881.h"
#include "Lights.h"
#include "CD74HC4067.h"
#include "HCSR04.h"

int actionGroups[][] = {
  {DIRECTION_FORWARDS, DIRECTION_BACKWARDS, DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_STOP},
  {LIGHT_ON, LIGHT_OFF},
  {SENSOR_READ}
}

// Initialise Modules
HG7881 motors;
Lights lights;
CD74HC4067 mux1(A1);
HCSR04 sensor;

void setup() 
{
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

  int action = -1;
  int group = getActionGroup(value, actionGroups, action);

  switch (group) 
  {
    case 0:
      motors.doAction(action);
      break;
    case 1:
      lights.doAction(action);
      break;
    case 2:
      int distance = sensor.doPing();
      if (distance < 4)
      {
        channel = 10; //@todo will be replaced
      }
      break;
    default:
      Serial.println("Unknown group or no match");
      break;
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

int getActionGroup(int value, int &actionGroups, int *action);
{
  for (int i; i  < (int)( sizeof(actionGroups) / sizeof(actionGroups[0])); i ++)
  {
    int match = getMatch(value, actionGroups[i], (int) (sizeof(actionGroups[i]) / sizeof(actionGroups[i][0]));
    if (match > -1)
    {
      action = match;
      return i;
    }
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
