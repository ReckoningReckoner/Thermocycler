//
// Created by Viraj Bangari on 2017-03-09.
//

#ifndef SRC_ROTARYENCODERPOSITION_H
#define SRC_ROTARYENCODERPOSITION_H

#include <RotaryEncoder.h>

class RotaryEncoderPosition {
    RotaryEncoder rotaryEncoder;
    long oldpos = 0;
    public:
        RotaryEncoderPosition(int pinA, int pinB) : rotaryEncoder(pinA, pinB){};
        int rotationDirection() {
            int newpos = rotaryEncoder.position();
            if (newpos > oldpos) {
                oldpos = newpos;
                return 1;
            } else if (newpos < oldpos) {
                oldpos = newpos;
                return -1;
            } else {
                return 0;
            }
        }
};


#endif //SRC_ROTARYENCODERPOSITION_H
