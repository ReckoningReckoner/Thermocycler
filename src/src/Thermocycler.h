#ifndef THERMOCYCLER_H
#define THERMOCYCLER_H
#include "Relay.h"
#include "TemperatureSensor.h"

class Thermocycler {
    Relay fan;
    Relay heatSource;
    TemperatureSensor* temperatureSensor;
    public:
        Thermocycler(int pin_fan, int pin_heatSource);
        int adjustTemperature(double currentTemperature, double goalTemperature);
        void fail();
};
#endif
