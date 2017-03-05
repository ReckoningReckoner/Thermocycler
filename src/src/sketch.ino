#include "constants.h"
#include "Cycles.h"
#include "Relay.h"

int pin = 22;
void setup()
{
    pinMode(pin, OUTPUT);
}

void loop()
{
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
    delay(1000);
}
