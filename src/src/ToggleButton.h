#ifndef ToggleButton_h
#define ToggleButton_h

class ToggleButton {
    int pin;
    long delay;
    long lastPressed;
    bool state;
    public:
        ToggleButton(int, bool, long);
        void setOn();
        void setOff();
        bool canSwitch();
        bool isOn();
        int getPin();
};
#endif
