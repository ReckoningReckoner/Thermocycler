#ifndef Button_h
#define Button_h

class Button {
    protected:
        int pin;
    public:
        Button(int);
        bool isOn();
};

#endif
