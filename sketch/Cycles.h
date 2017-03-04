#ifndef Cycles_h
#define Cycles_h

#include "constants.h"

class Cycles {
    long cycle_time[NUM_TEMPERATURES];
    double temperatures[NUM_TEMPERATURES];
    unsigned short number_of_cycles;
    unsigned short current_cycle;
    long time_since_start;
    long time_at_last_cycle_change;
    unsigned short cycles_completed;
    public:
        Cycles();
        bool isValid();
        int setTemperature(unsigned short, double);
        int setTime(unsigned short, long);
        short setGoalTemperatureAndGetCycle(long, double*);
        bool isFinished();
        int setNumberOfCycles(unsigned short);
        void reset();
        double getTemperature(unsigned short);
        long getTime(unsigned short);
        unsigned short getNumberOfCycles();
    private:
        void incrementCycle(unsigned short*);
};
#endif
