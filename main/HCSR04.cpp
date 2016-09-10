#include "Arduino.h"
#include "HCSR04.h"

HCSR04::HCSR04()
{
    pinMode( TRIGGER_PIN, OUTPUT );
    pinMode( ECHO_PIN, INPUT);

    digitalWrite(TRIGGER_PIN, LOW);
}
long HCSR04::doPing()
{
    long duration, inches;
    int value;

    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIGGER_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
    inches = microsecondsToInches(duration); 
    return inches;
}
long HCSR04::microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
