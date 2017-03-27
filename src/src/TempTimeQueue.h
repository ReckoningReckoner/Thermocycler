#ifndef TEMPTIMEQUEUE_H
#define TEMPTIMEQUEUE_H

struct _TempTime {
    unsigned long time;
    double temperature;
    _TempTime(unsigned long _time, double _temperature) {
        time = _time;
        temperature = _temperature;
    }
};

#define TEMPTIME_MAX_SIZE 10
/*
 * This will dynamically do a least sq fitting of the temperature rates for
 * the last 2 to TEMPTIME_MAX_SIZE data points.
 */
class TempTimeQueue {
    int currentSize = 0;
    _TempTime* values[TEMPTIME_MAX_SIZE];
    int startIndex = 0;
    int endIndex = 0;

    double sumTimes = 0;
    double sumTemps = 0;
    double sumTimeTemps = 0;
    double sumTimeSq = 0;

    void pop();
    public:
        void push(unsigned long time, double temperature);
        void clear();
        double getTemperatureRate();
        ~TempTimeQueue();
};

#endif
