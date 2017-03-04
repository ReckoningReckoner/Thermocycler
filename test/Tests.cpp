#include<iostream>
#include <assert.h>
#include "../sketch/Cycles.h"

void invalidCycles() {
    std::cout << "Running cycles permission tests...\n";
    Cycles cycle;
    assert(!cycle.isValid());

    assert(cycle.setTime(99, 3) == -1);
    assert(cycle.setTemperature(99, 3) == -1);
    assert(cycle.setTime(0, 0) == -1);
    assert(cycle.setTemperature(0, 150) == -1);
    assert(cycle.setTemperature(0, 0) == -1);
    assert(!cycle.isValid());

    assert(cycle.setTime(0, 10) == 0);
    assert(cycle.setTime(2, 20) == 0);
    assert(cycle.setTemperature(0, 90) == 0);
    assert(cycle.setTemperature(0, 65.5) == 0);
    assert(cycle.setTemperature(0, 73.5) == 0);

    assert(cycle.setNumberOfCycles(0) == -1);
    assert(cycle.setNumberOfCycles(-13) == -1);
    assert(cycle.setNumberOfCycles(900) == -1);

    assert(!cycle.isValid());

    assert(cycle.setTime(1, 20) == 0);
    assert(cycle.setNumberOfCycles(4) == 0);
    assert(cycle.isValid());
}

void timedCycles() {
    std::cout << "Running simulated cycle...\n";
    Cycles cycle;

    long time1 = 10;
    long time2 = 20;
    long time3 = 10;
    cycle.setTime(0, time1);
    cycle.setTime(1, time2);
    cycle.setTime(2, time3);

    double temp1 = 90.0;
    double temp2 = 63.2;
    double temp3 = 77.5;
    cycle.setTemperature(0, temp1);
    cycle.setTemperature(1, temp2);
    cycle.setTemperature(2, temp3);

    unsigned short num_cycles = 3;
    cycle.setNumberOfCycles(num_cycles);
    assert(cycle.isValid());
}

int main() {
    std::cout << "Starting Tests\n";
    invalidCycles();
    timedCycles();

    std::cout << "All tests passed!\n";
    return 0;
}
