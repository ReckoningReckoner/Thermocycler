#include "Button.h"

Button button(34);
int pinLED = 22;
void setup()
{
    pinMode(pinLED, OUTPUT);
}

void loop()
{
    if (button.isOn()) {
        digitalWrite(pinLED, HIGH);
    } else {
        digitalWrite(pinLED, LOW);
    }
}
