#include <stdlib.h>
#include "Cycles.h"

Cycles::Cycles() {
    number_of_cycles = 0;
    for (int i = 0; i < NUM_TEMPERATURES; i++) {
       temperatures[i] = MIN_TEMPERATURE;
       cycle_time[i] = 0;
    }

    /* These values must be reset */
    time_since_start = 0;
    time_at_last_cycle_change = 0;
    current_cycle = 0;
    cycles_completed = 0;
    is_ramping = true;
}

void Cycles::reset() {
    current_cycle = 0;
    cycles_completed = 0;
    time_since_start = 0;
    time_at_last_cycle_change = 0;
    is_ramping = true;
}

void Cycles::incrementCycle(unsigned short* num_cycles) {
    if (*num_cycles < NUM_TEMPERATURES - 1) {
        (*num_cycles)++;
    } else {
        (*num_cycles) = 0;
    }
}

bool Cycles::isFinished() {
    return cycles_completed >= number_of_cycles * NUM_TEMPERATURES;
}

/*
 * Retruns -2 if the current cycle is invalid
 * Returns -1 if the cycles are finished but the thermocycler is not yet reset
 */
short Cycles::setGoalTemperatureAndGetCycle(unsigned long time, double*
        goalTemperature, double currentTemperature) {
    if (current_cycle >= NUM_TEMPERATURES) {
        *goalTemperature = -1;
        return -2;
    } else if (isFinished()) {
        *goalTemperature = -1;
        return -1;
    }

    if (is_ramping) {
        if (fabs(currentTemperature - *goalTemperature) <= RAMPING_TEMPERATURE_DIFFERENCE) {
            is_ramping = false;
            time_at_last_cycle_change = time;
        }
    }

    if (!is_ramping) {
        time_since_start = time - time_at_last_cycle_change;
        if (time_since_start >= cycle_time[current_cycle]) {
            incrementCycle(&current_cycle);
            cycles_completed++;
            is_ramping = true;
            time_since_start = 0;
        }
    }

    if (!isFinished()) {
        *goalTemperature = temperatures[current_cycle];
        return current_cycle;
    } else {
        *goalTemperature = -1;
        return -1;
    }
}

bool Cycles::isRamping() {
    return is_ramping;
}

int Cycles::setTime(unsigned short num_cycles, long t) {
    if (num_cycles < NUM_TEMPERATURES && 0 < t && t <= MAX_TIME) {
        cycle_time[num_cycles] = t;
        return 0;
    }
    return -1;  
}

int Cycles::setTemperature(unsigned short num_cycles, double t) {
    if (num_cycles < NUM_TEMPERATURES &&
        MIN_TEMPERATURE <= t && t <= MAX_TEMPERATURE) {
        temperatures[num_cycles] = t;
        return 0;
    }
    return -1;  
}

unsigned short Cycles::getNumberOfCycles() {
    return number_of_cycles;
}

int Cycles::setNumberOfCycles(unsigned short num) {
    if (num != 0 && num <= MAX_CYCLES) {
        number_of_cycles = num;
        return 0;
    }
    return -1;
}

long Cycles::getTime(unsigned short cycle_number) {
    if (cycle_number < NUM_TEMPERATURES) {
        return cycle_time[cycle_number];
    }
    return -1;
}

double Cycles::getTemperature(unsigned short cycle_number) {
    if (cycle_number < NUM_TEMPERATURES) {
        return temperatures[cycle_number];
    }
    return -1;
}

bool Cycles::isValid() {
    if (number_of_cycles <= 0 || number_of_cycles > MAX_CYCLES) {
        return false;
    }

    if (cycles_completed > 0) {
        return false;
    }

    if (current_cycle > 0) {
        return false;
    }

    if (time_since_start != 0 || time_at_last_cycle_change != 0) {
        return false;
    }
    
    if (!is_ramping) {
        return false;
    }

    for (int i = 0; i < NUM_TEMPERATURES; i++){
        if (cycle_time[i] <= 0 ||
            cycle_time[i] > MAX_TIME ||
            temperatures[i] < MIN_TEMPERATURE ||
            temperatures[i] > MAX_TEMPERATURE) {
            return false;
        }
    }

    return true;
}
