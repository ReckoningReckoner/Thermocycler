#ifndef Relay_h
#define Relay_h
class Relay {
    int pin;
    bool current_state = false;
    public:
        Relay(int);
        void turnOn();
        void turnOff();
        bool isOn();
};
#endif
