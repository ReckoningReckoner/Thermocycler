#include "Button.h"
#include "Arduino.h"

/*
 * Uses internal pullup resistors.
 * One end of the button must be connected
 * to the pin. The other end should be grounded
 */
Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isOn() {
   return !digitalRead(pin);
}
