#ifndef Cycles_h
#define Cycles_h

#include "constants.h"
#include  <math.h>
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
 *     short cycleNum = setGoalTemeprature(millis(), &goalTemperature, currentTemperature);
 *     if (cycleNum >= 0 || goalTemperature >= MIN_TEMPERATURE) {
 *         do stuff with goalTemeperature and cycleNum
 *     } else {
 *         handle the error
 *     }
 * }
 *
 * A cycle will only be valid in the following cases:
 * Number of cycles is > 0 and <= MAX_CYCLES
 * Temperature is between MIN and MAXTEMPERATURE
 * Cycle time is > 0 and less than MAX TIME
 *
 * The default cycles times are set to 0.
 * The default temperatures are set to MIN TEMPERATURE
 * The default number of cycles is 0.
 * 
 * If a cycle is stopped, it must be reset using the cycle.reset()
 * method before starting again.
 */
class Cycles {
    unsigned long cycle_time[NUM_TEMPERATURES];
    double temperatures[NUM_TEMPERATURES];
    unsigned short number_of_cycles;
    unsigned short current_cycle;
    unsigned long time_since_start;
    unsigned long time_at_last_cycle_change;
    unsigned short cycles_completed;
    bool is_ramping;

    public:
        Cycles();
        bool isValid();
        int setTemperature(unsigned short, double);
        int setTime(unsigned short, long);
        short setGoalTemperatureAndGetCycle(unsigned long, double*, double);
        bool isFinished();
        int setNumberOfCycles(unsigned short);
        void reset();
        double getTemperature(unsigned short);
        long getTime(unsigned short);
        unsigned long getTimeSinceStart();
        unsigned short getNumberOfCycles();
        bool isRamping();
    private:
        void incrementCycle(unsigned short*);
};
#endif

