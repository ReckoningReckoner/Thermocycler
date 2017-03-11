#define DEBUG

#include "Arduino.h"
#include "ToggleButton.h"
#include "Interface.h"
#include "RotaryEncoderPosition.h"


# define togglePin 20
ToggleButton toggleButton(togglePin, false, 300);
# define statePin 19
ToggleButton stateButton(statePin, false, 300);

RotaryEncoderPosition encoder(2, 3);

Cycles cycle;
/* RS E D4 D5 D6 D7 */
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Interface interface(&lcd, &cycle);


/* Interrupt method */
void toggleSettings() {
    if (!stateButton.isOn() && toggleButton.canSwitch()) {
        interface.incrementIndex();
        #if defined(DEBUG)
        Serial.print("Toggle Button Pressed ");
        Serial.println(millis());
        #endif
    }
}

/* Interrupt method */
void changeState() {
    if (stateButton.canSwitch()) {
        #if defined(DEBUG)
        Serial.print("State Button Pressed ");
        Serial.println(millis());
        #endif
        if (stateButton.isOn()) { // In the middle of cycle
            stateButton.setOff();
            cycle.reset();
        }
        else if (cycle.isValid()) {
            stateButton.setOn();
        }
    }
}

void doInterface() {
    int direction = encoder.rotationDirection();
    if (direction == 1) {
        #if defined(DEBUG)
        Serial.print("CW");
        Serial.println(millis());
        #endif
        interface.adjustSetting(true); // increase
    } else if (direction == -1) {
        #if defined(DEBUG)
        Serial.print("CCW");
        Serial.println(millis());
        #endif
        interface.adjustSetting(false); // decrease
    }
}

void setup() {
    #if defined(DEBUG)
    Serial.begin(9600);
    #endif
    attachInterrupt(digitalPinToInterrupt(togglePin),
                    toggleSettings,
                    RISING);
    attachInterrupt(digitalPinToInterrupt(statePin),
                    changeState,
                    RISING);
}


void loop() {
    while (!stateButton.isOn()) { // Get User Settings
        doInterface();
    }

    while (stateButton.isOn()) { // Run Thermocycle
    }

    if (cycle.isFinished()){
        cycle.reset();
        stateButton.setOff();
    }
}
