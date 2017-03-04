#ifndef Cycles_h
#define Cycles_h

#include "constants.h"
/**
 * This class is for keeping track of the current cycle, and stores the user's input.
 * The setTemperature and setTime functions are used for storing inputs.
 * isValid is for validitaing the user input and making sure its safe to start a cycle.
 * isFinished checks if the cycle is finished.
 * 
 * The important part of this code is the setGoalTemperatureAndGetCycle function.
 * It is essentially run like this:
 * 
 * double goalTemperature;
 * while(!cycles.isFinished()) {
 *     short cycleNum = setGoalTemeprature(millis(), &goalTemperature);
 *     if (cycleNum >= 0 || goalTemperature >= MIN_TEMPERATURE) {
 *         do stuff with goalTemeperature and cycleNum
 *     } else {
 *         handle the error
 *     }
 * }
 */
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
