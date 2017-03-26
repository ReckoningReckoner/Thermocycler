#include "../src/Cycles.h"
#include "../src/constants.h"
#include "CycleTests.h"
#include <assert.h>
#include<iostream>
#include "../src/Interface.h"

void invalidCycles() {
    std::cout << "Running cycles permission tests...\n";
    Cycles cycle;
    assert(!cycle.isValid());

    assert(cycle.setTime(99, 3) == -1);
    assert(cycle.setTemperature(99, 3) == -1);
    assert(cycle.setTime(0, 0) == -1);
    assert(cycle.setTime(0, 2147483647) == -1);
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

    cycle.reset();
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

    unsigned short num_cycles = 2;
    cycle.setNumberOfCycles(num_cycles);
    assert(cycle.isValid());

    long simulatedTime = 0;
    short simulatedCycle = 0;
    double simulatedTemperature = 0;

    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp1/2);
    assert(simulatedCycle == 0);
    assert(simulatedTemperature == temp1);
    assert(!cycle.isFinished());

    simulatedTime = 10;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp1);
    assert(simulatedCycle == 0);
    assert(simulatedTemperature == temp1);
    assert(!cycle.isFinished());

    simulatedTime = 19;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp1);
    assert(simulatedCycle == 0);
    assert(simulatedTemperature == temp1);
    assert(!cycle.isFinished());

    simulatedTime = 22;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp1);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());

    simulatedTime = 30;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2/2);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());

    simulatedTime = 60;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2/2);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());

    simulatedTime = 90;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2 - 0.01);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());

    simulatedTime = 111;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2 - 0.01);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 130;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3/2);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 131;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 135;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 142;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == 0);
    assert(simulatedTemperature == temp1);
    assert(!cycle.isFinished());


    simulatedTime = 153;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp1 + 0.03);
    assert(simulatedCycle == 0);
    assert(simulatedTemperature == temp1);
    assert(!cycle.isFinished());


    simulatedTime = 163;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());

    simulatedTime = 164;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2);
    assert(simulatedCycle == 1);
    assert(simulatedTemperature == temp2);
    assert(!cycle.isFinished());


    simulatedTime = 184;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp2);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 185;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == 2);
    assert(simulatedTemperature == temp3);
    assert(!cycle.isFinished());

    simulatedTime = 195;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == -1);
    assert(simulatedTemperature == -1);
    assert(cycle.isFinished());

    simulatedTime = 999;
    simulatedCycle = cycle.setGoalTemperatureAndGetCycle(simulatedTime, 
                                                         &simulatedTemperature, temp3);
    assert(simulatedCycle == -1);
    assert(simulatedTemperature == -1);
    assert(cycle.isFinished());

    assert(!cycle.isValid());
    cycle.reset();
    assert(cycle.isValid());
}

void interfaceTests() {
    std::cout << "interface tests" << std::endl;
    Cycles cycle;
    assert(!cycle.isValid());
    Interface interface(&cycle);

    assert(interface.index == 0);
    interface.incrementIndex();
    assert(interface.index == 1);
    interface.incrementIndex();
    assert(interface.index == 2);
    interface.incrementIndex();
    assert(interface.index == 3);
    interface.incrementIndex();
    assert(interface.index == 4);
    interface.incrementIndex();
    assert(interface.index == 5);
    interface.incrementIndex();
    assert(interface.index == 6);
    interface.incrementIndex();
    assert(interface.index == 0);

    // Index is 0
    interface.adjustSetting(true);
    assert(cycle.getTemperature(0) == MIN_TEMPERATURE + interface.temperatureIncrement);
    interface.adjustSetting(false);
    assert(cycle.getTemperature(0) == MIN_TEMPERATURE);
    interface.adjustSetting(false);
    assert(cycle.getTemperature(0) == MIN_TEMPERATURE);
    cycle.setTemperature(0, MAX_TEMPERATURE);
    interface.adjustSetting(true);
    assert(cycle.getTemperature(0) == MAX_TEMPERATURE);

    interface.incrementIndex(); // Should be 2
    assert(cycle.getTime(0) == 0);
    interface.adjustSetting(false);
    assert(cycle.getTime(0) == 0);
    interface.adjustSetting(true);
    assert(cycle.getTime(0) == interface.timeIncrement);
    interface.adjustSetting(true);
    cycle.setTime(0, MAX_TIME);
    assert(cycle.getTime(0) == MAX_TIME);

    interface.incrementIndex(); // Should be 3
    interface.adjustSetting(true);
    assert(cycle.getTemperature(1) == MIN_TEMPERATURE + interface.temperatureIncrement);
    interface.adjustSetting(false);
    assert(cycle.getTemperature(1) == MIN_TEMPERATURE);
    interface.adjustSetting(false);
    assert(cycle.getTemperature(1) == MIN_TEMPERATURE);
    cycle.setTemperature(1, MAX_TEMPERATURE);
    interface.adjustSetting(true);
    assert(cycle.getTemperature(1) == MAX_TEMPERATURE);
}
