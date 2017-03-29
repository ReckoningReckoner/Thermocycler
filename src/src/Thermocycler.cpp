#include "Thermocycler.h"
#include "constants.h"

Thermocycler::Thermocycler(int pin_fan, int pin_heatSource):
    fan(pin_fan), heatSource(pin_heatSource) {
    heatSource.turnOff();
    fan.turnOff();
};


int Thermocycler::adjustTemperature(double currentTemperature,
        double goalTemperature, unsigned long time) {
    queue.push(time, currentTemperature);
    if (currentTemperature > goalTemperature) {
        if (currentTemperature - goalTemperature > MAINTAIN_TEMPERATURE) {
            heatSource.turnOff();
            fan.turnOn();
        } else {
            heatSource.turnOff();
            fan.turnOff();
        }
    } else {
        if (goalTemperature - currentTemperature > MAINTAIN_TEMPERATURE) {
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

void Thermocycler::reset() {
    heatSource.turnOff();
    fan.turnOff();
    queue.clear();
}
