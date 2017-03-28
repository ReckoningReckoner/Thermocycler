#include "TempTimeQueue.h"

void TempTimeQueue::push(unsigned long time, double temperature) {
    if (currentSize == TEMPTIME_MAX_SIZE) {
        pop();
    }

    _TempTime * tempTime = new _TempTime(time, temperature);
    if (currentSize != 0) {
        endIndex = (endIndex + 1) % TEMPTIME_MAX_SIZE;
    }

    /* Update linear regression */
    sumTimes += (double) tempTime->time;
    sumTemps += tempTime->temperature;
    sumTimeTemps += (double)tempTime->time * tempTime->temperature;
    sumTimeSq += (double)tempTime->time * (double)tempTime->time;
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
    sumTimes -= (double)t->time;
    sumTemps -= t->temperature;
    sumTimeTemps -= (double)t->time * t->temperature;
    sumTimeSq -= (double)t->time * (double)t->time;
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
    if (currentSize > 1) {
        double num = sumTimeTemps/currentSize - sumTimes/currentSize * sumTemps/currentSize;
        double denom = sumTimeSq / currentSize - (sumTimes * sumTimes)/(currentSize * currentSize);
        return num / denom;
    } else {
        return 0;
    }
}
