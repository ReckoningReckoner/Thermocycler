#include "Relay.h"
#include "Arduino.h"

Relay::Relay(int pin) {
    this->pin = pin;
}

void Relay::turnOn() {
    if (current_state) {
        return;
    } else {
        digitalWrite(pin, HIGH);
        current_state = true;
    }
}

void Relay::turnOff() {
    if (!current_state) {
        return;
    } else {
        digitalWrite(pin, LOW);
        current_state = false;
    }
}

bool Relay::isOn() {
    return current_state;
}

