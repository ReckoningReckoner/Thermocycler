#ifndef Interface_h
#define Interface_h

#ifndef TESTING
#include <LiquidCrystal.h>
#endif

#include "Cycles.h"
const double temperatureIncrement = 0.5;
const long timeIncrement = 30000; // 30 seconds

class Interface {
    Cycles* cycle;
#ifndef TESTING
    LiquidCrystal* lcd;
#endif
    unsigned short maxIndex;
    public:
#ifndef TESTING
        Interface(LiquidCrystal*, Cycles*);
#endif
        unsigned short index;
        Interface(Cycles*);
        void adjustSetting(bool);
        void incrementIndex();
};
#endif