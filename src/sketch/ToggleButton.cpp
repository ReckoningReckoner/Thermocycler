#include "Button.h"
#include "ToggleButton.h"
#include "Arduino.h"

ToggleButton::ToggleButton(int pin, bool state, long delay) {
    this->pin = pin;
    this->delay = delay;
    this->state = state;
    this->lastPressed = millis();
}

int ToggleButton::getPin() {
    return pin;
}

bool ToggleButton::isOn() {
    return state;
}

/*
 * Returns true if there was a change in state
 */
bool ToggleButton::canSwitch() {
    long timePressed = millis();
    if (timePressed - lastPressed > delay)
    {
        lastPressed = timePressed;
        return true;
    }
    return false;
}

void ToggleButton::setOn() {
    state = true;
}

void ToggleButton::setOff() {
    state = false;
}
