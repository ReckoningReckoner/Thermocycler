#include "Thermocycler.h"
#include "constants.h"

Thermocycler::Thermocycler(int pin_fan, int pin_heatSource, int pin_lid):
    fan(pin_fan), heatSource(pin_heatSource), lid(pin_lid) {
    heatSource.turnOff();
    fan.turnOff();
    lid.turnOff();
};


double Thermocycler::adjustTemperature(double currentTemperature,
        double goalTemperature, unsigned long time) {
    lid.turnOn(); // Turn on the lid. Otherwise fan cannot be used!
    queue.push(time/1000.0, currentTemperature);

    double rate = queue.getTemperatureRate();
    double predictedTemperature;
    if (rate >= 0) { // Heating
        const int heatingTimeDiff = 17;
        predictedTemperature = currentTemperature + rate * heatingTimeDiff;
    } else { // Cooling
        const int coolingTimeDiff = 10; // seconds
        predictedTemperature = currentTemperature + rate * coolingTimeDiff;
    }

    if (fabs(predictedTemperature - goalTemperature) <= MAINTAIN_TEMPERATURE) { // Maintain
        heatSource.turnOff();
        fan.turnOff();
    }
    else if (predictedTemperature > goalTemperature) { // Going to be too hot
        heatSource.turnOff();
        fan.turnOn();
    } else { // Going to be too Cold
        heatSource.turnOn();
        fan.turnOff();
    }
    delay(200);
    return predictedTemperature;
}

void Thermocycler::powerFan() {
    lid.turnOn();
    fan.turnOn();
    heatSource.turnOff();
    delay(200);
}

void Thermocycler::powerHeat() {
    lid.turnOn();
    fan.turnOff();
    heatSource.turnOn();
    delay(200);
}

void Thermocycler::fail() {
    reset();
}

void Thermocycler::reset() {
    lid.turnOff();
    heatSource.turnOff();
    fan.turnOff();
    queue.clear();
}
