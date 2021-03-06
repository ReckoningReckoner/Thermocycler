#ifndef THERMOCYCLER_H
#define THERMOCYCLER_H
#include "Relay.h"
#include "TemperatureSensor.h"
#include "TempTimeQueue.h"

class Thermocycler {
    Relay fan;
    Relay heatSource;
    Relay lid;

    public:
        TempTimeQueue queue;
        Thermocycler(int pin_fan, int pin_heatSource, int pin_lid);
        double adjustTemperature(double currentTemperature,
                                 double goalTemperature,
                                 unsigned long time);
        void fail();
        void reset();
        void powerFan();
        void powerHeat();
};
#endif
