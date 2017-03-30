#ifndef constants_h
#define constants_h

const int NUM_TEMPERATURES = 3;
const long MAX_TIME = 1800000; // 30 Minutes
const unsigned short MAX_CYCLES = 300;

const double MIN_TEMPERATURE = 30;
const double MAX_TEMPERATURE = 105;

const double DANGER_TEMPERATURE = 130;

const double SAFE_TEMPERATURE = 35;
const double RAMP_TEMPERATURE = 90;

const double RAMPING_TEMPERATURE_DIFFERENCE = 2.0;// Temperature difference for ramp rate
const double MAINTAIN_TEMPERATURE = 1.5;
#endif
