#include "Button.h"
#include "Arduino.h"

Button::Button(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

bool Button::isOn() {
   return !digitalRead(pin);
}
