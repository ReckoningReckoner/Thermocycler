/*
 * APSC200 Thermoycler Project
 * Year: 2017
 * Author: Viraj Bangari
 */
#include "Arduino.h"
#include "ToggleButton.h"
#include "Interface.h"
#include <LiquidCrystal.h>
#include "RotaryEncoderPosition.h"


# define togglePin 20
ToggleButton toggleButton(togglePin, false, 300);
# define statePin 19
ToggleButton stateButton(statePin, false, 300);
RotaryEncoderPosition encoder(2, 3);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS E D4 D5 D6 D7
Cycles cycle;
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
        }
        else if (!stateButton.isOn() && cycle.isValid()) { // Start your cycle
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
                    toggleSettings, RISING);
    attachInterrupt(digitalPinToInterrupt(statePin),
                    changeState, RISING);
}


void loop() {
    interface.reset();
    cycle.reset();
    while (!stateButton.isOn()) { // Get User Settings
        doInterface();
    }

    double goalTemperature = 0;
    lcd.clear();
    unsigned long timeStart = millis();
    while (stateButton.isOn() && !cycle.isFinished()) { // Run Thermocycle
        unsigned long time = millis() - timeStart;
        short cycleNum =
                cycle.setGoalTemperatureAndGetCycle(time,
                                                    &goalTemperature, goalTemperature);
        interface.displayCycleInfo(&cycleNum, &time, &goalTemperature);
    }

    if (cycle.isFinished()) {
        stateButton.setOff();
    }
}
