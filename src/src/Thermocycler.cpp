#include "Thermocycler.h"

Thermocycler::Thermocycler(int pin_fan, int pin_heatSource):
    fan(pin_fan), heatSource(pin_heatSource) {
    heatSource.turnOff();
    fan.turnOff();
};

int Thermocycler::adjustTemperature(double currentTemperature, double goalTemperature) {

}

void Thermocycler::fail() {
    heatSource.turnOff();
    fan.turnOff();
}
