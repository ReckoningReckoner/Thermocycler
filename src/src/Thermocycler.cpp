#include "Thermocycler.h"
#include "Arduino.h"

Thermocycler::Thermocycler(int pin_fan, int pin_heatSource):
    fan(pin_fan), heatSource(pin_heatSource) {
    heatSource.turnOff();
    fan.turnOff();
};

int Thermocycler::adjustTemperature(double currentTemperature, double goalTemperature) {
    if (currentTemperature > goalTemperature) {
        if (currentTemperature - goalTemperature > maintainTemperature) {
            heatSource.turnOff();
            fan.turnOn();
        } else {
            heatSource.turnOff();
            fan.turnOff();
        }
    } else {
        if (goalTemperature - currentTemperature > maintainTemperature) {
            heatSource.turnOn();
            fan.turnOff();
        } else {
            heatSource.turnOff();
            fan.turnOff();
        }
    }
    delay(200);
    return 0;
}

void Thermocycler::fail() {
    heatSource.turnOff();
    fan.turnOff();
}
