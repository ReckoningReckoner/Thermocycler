#include "Interface.h"
#include "constants.h"

/* Interrupt pins for Arduino MEGA
 * 2, 3, 18, 19, 20, 21
 */
#ifndef TESTING
Interface::Interface(LiquidCrystal* lcd, Cycles* cycle) {
    this->lcd = lcd;
    this->cycle = cycle;
    maxIndex = 2 * NUM_TEMPERATURES;
    index = 0;
}
#endif

Interface::Interface(Cycles* cycle) {
    this->cycle = cycle;
    maxIndex = 2 * NUM_TEMPERATURES;
    index = 0;
}

void Interface::incrementIndex() {
    if (index < maxIndex) {
        index++;
    } else {
        index = 0;
    }
}

void Interface::adjustSetting(bool increase) {
    if (index == maxIndex) { // Number of cycles
        unsigned short currentCycles = cycle->getNumberOfCycles();
        if (increase) {
            currentCycles++;
        } else {
            currentCycles--;
        }
        cycle->setNumberOfCycles(currentCycles);
    } else if (index % 2 != 0) { // Time
        unsigned short cycleIndex = index/2;
        long currentTime = cycle->getTime(cycleIndex);
        if (increase) {
            currentTime += timeIncrement;
        } else {
            currentTime -= timeIncrement;
        }
        cycle->setTime(cycleIndex, currentTime);
    } else { // Temperature
        unsigned short cycleIndex = index/2;
        double currentTemperature = cycle->getTemperature(cycleIndex);
        if (increase) {
            currentTemperature += temperatureIncrement;
        } else {
            currentTemperature -= temperatureIncrement;
        }
        cycle->setTemperature(cycleIndex, currentTemperature);
    }
}
