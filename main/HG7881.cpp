#include "Arduino.h"
#include "HG7881.h"

HG7881::HG7881()
{
    pinMode( MOTOR_L_DIR, OUTPUT );
    pinMode( MOTOR_L_PWM, OUTPUT );
    pinMode( MOTOR_R_DIR, OUTPUT );
    pinMode( MOTOR_R_PWM, OUTPUT );

    // Stop but don't add delay
    _lastAction = DIRECTION_STOP;
    stop(false);
}
void HG7881::doAction(int direction)
{
    Serial.print("Motors: ");
    Serial.println(direction);
    
    if (direction == _lastAction) return;

     // Stop drive if not already stopped
    if (_lastAction != DIRECTION_STOP) stop();

    // Set last action
    _lastAction = direction;

    switch(direction)
    {
        case DIRECTION_FORWARDS:
            Serial.println("Forwards");
            digitalWrite( MOTOR_L_DIR, MOTOR_FORWARD );
            analogWrite( MOTOR_L_PWM, MOTOR_FORWARD_SPEED );
            digitalWrite( MOTOR_R_DIR, MOTOR_FORWARD );
            analogWrite( MOTOR_R_PWM, MOTOR_FORWARD_SPEED );
            break;
        case DIRECTION_BACKWARDS:
            Serial.println("Backwards");
            digitalWrite( MOTOR_L_DIR, MOTOR_REVERSE );
            analogWrite( MOTOR_L_PWM, MOTOR_REVERSE_SPEED );
            digitalWrite( MOTOR_R_DIR, MOTOR_REVERSE );
            analogWrite( MOTOR_R_PWM, MOTOR_REVERSE_SPEED );
            break;
        case DIRECTION_LEFT:
            Serial.println("Left");
            digitalWrite( MOTOR_L_DIR, MOTOR_REVERSE );
            analogWrite( MOTOR_L_PWM, MOTOR_REVERSE_SPEED );
            break;
        case DIRECTION_RIGHT:
            Serial.println("Right");
            digitalWrite( MOTOR_R_DIR, MOTOR_REVERSE );
            analogWrite( MOTOR_R_PWM, MOTOR_REVERSE_SPEED );
            break;
        default:
            break;
    }
}

void HG7881::stop()
{
  stop(true);
}
void HG7881::stop(bool wait)
{
    Serial.println("Stopping");
    
    digitalWrite( MOTOR_L_DIR, LOW );
    digitalWrite( MOTOR_L_PWM, LOW );
    digitalWrite( MOTOR_R_DIR, LOW );
    digitalWrite( MOTOR_R_PWM, LOW );

    if (wait) delay( MOTOR_DELAY );
}
