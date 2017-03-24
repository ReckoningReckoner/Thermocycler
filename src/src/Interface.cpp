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

    lcd->begin(16, 2);
    updateLCD();
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
    #ifndef TESTING
    updateLCD();
    #endif
}

void Interface::reset() {
    index = 0;
    #ifndef TESTING
    updateLCD();
    #endif
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

        #ifndef TESTING
        lcd->setCursor(0, 1);
        lcd->print("   ");
        lcd->setCursor(0, 1);
        lcd->print(cycle->getNumberOfCycles());
        #endif
    } else if (index % 2 != 0) { // Time
        unsigned short cycleIndex = index/2;
        long currentTime = cycle->getTime(cycleIndex);
        if (increase) {
            currentTime += timeIncrement;
        } else {
            currentTime -= timeIncrement;
        }
        cycle->setTime(cycleIndex, currentTime);

        #ifndef TESTING
        lcd->setCursor(0, 1);
        lcd->print("     ");
        lcd->setCursor(0, 1);
        lcd->print(millisecondsToString(cycle->getTime(cycleIndex)));
        #endif
    } else { // Temperature
        unsigned short cycleIndex = index/2;
        double currentTemperature = cycle->getTemperature(cycleIndex);
        if (increase) {
            currentTemperature += temperatureIncrement;
        } else {
            currentTemperature -= temperatureIncrement;
        }
        cycle->setTemperature(cycleIndex, currentTemperature);

        #ifndef TESTING
        lcd->setCursor(0, 1);
        lcd->print("      ");
        lcd->setCursor(0, 1);
        lcd->print(cycle->getTemperature(cycleIndex));
        #endif
    }
}


#ifndef TESTING
void Interface::updateLCD() {
    lcd->clear();
    int cycleIndex = index/2;
    if (index == maxIndex) {
        lcd->setCursor(0, 0);
        lcd->print("Set # of cycles:");
        lcd->setCursor(0, 1);
        lcd->print(cycle->getNumberOfCycles());
    } else if (index % 2 != 0) { // Time
        lcd->setCursor(0, 0);
        lcd->print("Set time " + String(cycleIndex + 1) + ":");
        lcd->setCursor(0, 1);
        lcd->print(millisecondsToString(cycle->getTime(cycleIndex)));
    } else { // Time
        lcd->setCursor(0, 0);
        lcd->print("Set temp " + String(cycleIndex + 1) + ":");
        lcd->setCursor(0, 1);
        lcd->print(cycle->getTemperature(cycleIndex));
    }
}

void Interface::displayCycleInfo(short cycleNum, unsigned long time,
                                 double goalTemperature, double currentTemperature,
                                 bool isRamping) {
    lcd->setCursor(0, 0);
    lcd->print(cycleNum);
    lcd->print(" ");
    if (isRamping) {
        lcd->print("RAMP ");
    } else {
        lcd->print(millisecondsToString(time));
    }
    lcd->setCursor(0, 1);
    lcd->print(goalTemperature);
    lcd->print(" ");
    lcd->print(currentTemperature);
}

String millisecondsToString(unsigned long millis) {
    unsigned long seconds = millis/1000;
    String secondStr;
    if (seconds % 60 < 10) {
        secondStr = "0" + String(seconds % 60);
    } else {
        secondStr = String(seconds % 60);
    }

    String minuteStr;
    if (seconds/60 < 10) {
        minuteStr = "0" + String(seconds/60);
    } else {
        minuteStr = String(seconds/60);
    }
    return minuteStr + ":" + secondStr;
}
#endif
