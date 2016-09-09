#include "Arduino.h"
#include "Lights.h"

Lights::Lights()
{
    pinMode( LIGHT_PIN, OUTPUT );
    digitalWrite( LIGHT_PIN, LOW );

    _lastAction = LIGHT_OFF;
}
void Lights::doAction(int action)
{
    Serial.print("Lights: ");
    Serial.println(action);
    if (action == _lastAction) return;

    _lastAction = action;

    switch (action)
    {
        case LIGHT_ON:
            Serial.println("ON");
            digitalWrite(LIGHT_PIN, HIGH);
            break;
        case LIGHT_OFF:
        default:
            Serial.println("OFF");
            digitalWrite(LIGHT_PIN, LOW);
            break;
    }
}
