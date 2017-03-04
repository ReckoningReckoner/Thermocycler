#ifndef TemperatureSensor_h
#define TemperatureSensor_h
class TemperatureSensor {
    int pin;
    public:
        TemperatureSensor(int);
        double currentTemperature();
};
#endif
