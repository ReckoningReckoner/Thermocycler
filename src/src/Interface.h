#ifndef Interface_h
#define Interface_h

#ifndef TESTING
#include <LiquidCrystal.h>
String millisecondsToString(unsigned long millis);
#endif

#include "Cycles.h"
class Interface {
    Cycles* cycle;
#ifndef TESTING
    LiquidCrystal* lcd;
#endif
    unsigned short maxIndex;
    void updateLCD();
    public:
        const double temperatureIncrement = 0.5;
        const long timeIncrement = 30000; // 30 seconds
#ifndef TESTING
        Interface(LiquidCrystal*, Cycles*);
#endif
        unsigned short index;
        Interface(Cycles*);
        void adjustSetting(bool);
        void incrementIndex();
        void reset();
        void displayCycleInfo(short* cycleNum,
                              unsigned long* time,
                              double* goalTemperature);
};
#endif
