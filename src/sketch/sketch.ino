#include "constants.h"
#include "Cycles.h"
#include "Relay.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(NUM_TEMPERATURES);
    delay(1000);
}
