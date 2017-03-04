#include "Cycles.h"
#include "constants.h"

Cycles::Cycles() {
    for (int i = 0; i < NUM_TEMPERATURES; i++) {
       temperatures[i] = MIN_TEMPERATURE;
       cycle_time[i] = 0;
    }
}

void Cycles::incrementCycle(unsigned short* num_cycles) {
    if (*num_cycles < NUM_TEMPERATURES - 1) {
        (*num_cycles)++;
    } else {
        (*num_cycles) = 0;
    }
}

unsigned short Cycles::setGoalTemperatureAndGetCycle(long time, double*
        goalTemperature, unsigned short current_cycle) {
    if (current_cycle >= NUM_TEMPERATURES) {
        return -1;
    }
    else if (time >= cycle_time[current_cycle]) {
        incrementCycle(&current_cycle);
        (*goalTemperature) = temperatures[current_cycle];
        return current_cycle;
    } else {
        return current_cycle;
    }
}

int Cycles::setTime(unsigned short num_cycles, long t) {
    if (num_cycles < NUM_TEMPERATURES) {
        cycle_time[num_cycles] = t;
        return 0;
    }
    return -1;  
}

int Cycles::setTemperature(unsigned short num_cycles, double t) {
    if (num_cycles < NUM_TEMPERATURES && t >= MIN_TEMPERATURE) {
        temperatures[num_cycles] = t;
        return 0;
    }
    return -1;  
}

unsigned short Cycles::getNumberOfCycles() {
    return number_of_cycles;
}

int Cycles::setNumberOfCycles(unsigned short num) {
    if (num != 0) {
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
    if (number_of_cycles < 0) {
        return false;
    }

    for (int i = 0; i < NUM_TEMPERATURES; i++){
        if (cycle_time[i] >= 0 || temperatures[i] < MIN_TEMPERATURE || temperatures[i] > MAX_TEMPERATURE) {
            return false;
        }
    }

    return true;
}
