#ifndef TemperatureSensor_h
#define TemperatureSensor_h
#include "Arduino.h"
#include <max6675.h>

class TemperatureSensor {
    MAX6675 thermocouple;
    const short NUM_MEASUREMENTS = 15;
    public:
        TemperatureSensor(int pin_sck, int pin_cs, int pin_so):
                          thermocouple(pin_sck, pin_cs, pin_so) {};

        double currentTemperature() {
            double currentTemperature = 0;
            for (int i = 0; i < NUM_MEASUREMENTS; i++) {
                currentTemperature += thermocouple.readCelsius();
                delay(10);
            }
            return currentTemperature / NUM_MEASUREMENTS;
        };
};
#endif

