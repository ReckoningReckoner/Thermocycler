#include "TempTimeQueue.h"

void TempTimeQueue::push(double time, double temperature) {
    if (currentSize == TEMPTIME_MAX_SIZE) {
        pop();
    }

    _TempTime * tempTime = new _TempTime(time, temperature);
    if (currentSize != 0) {
        endIndex = (endIndex + 1) % TEMPTIME_MAX_SIZE;
    }

    /* Update linear regression */
    sumTimes += tempTime->time;
    sumTemps += tempTime->temperature;
    sumTimeTemps += tempTime->time * tempTime->temperature;
    sumTimeSq += tempTime->time * tempTime->time;
    /* update */

    values[endIndex] = tempTime;
    currentSize++;
}

void TempTimeQueue::pop() {
    if (currentSize == 0) {
        return;
    }

    _TempTime* t = values[startIndex];
    /* update regression */
    sumTimes -= t->time;
    sumTemps -= t->temperature;
    sumTimeTemps -= t->time * t->temperature;
    sumTimeSq -= t->time * t->time;
    /* end */
    delete t;

    if (currentSize == 1) {
        currentSize--;
    } else {
        startIndex = (startIndex + 1) % TEMPTIME_MAX_SIZE;
        currentSize--;
    }
}

void TempTimeQueue::clear() {
    for (int i = 0; i < currentSize; i++) {
        pop();
    }
    startIndex = 0;
    endIndex = 0;

    sumTimes = 0;
    sumTemps = 0;
    sumTimeTemps = 0;
    sumTimeSq = 0;
}

TempTimeQueue::~TempTimeQueue() {
    clear();
}

/* 
 * Linear regression formula
 * mean(xy) - mean(x)*mean(y)/(mean(x^2) - mean(x)^2)
 */
double TempTimeQueue::getTemperatureRate() {
    if (currentSize  > 5) {
        double num = currentSize * sumTimeTemps - sumTimes * sumTemps;
        double denom = currentSize * sumTimeSq - sumTimes * sumTimes;
        return num / denom;
    } else {
        return 0;
    }
}

