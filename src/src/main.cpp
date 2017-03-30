/*
 * APSC200 Thermoycler Project
 * Year: 2017
 * Author: Viraj Bangari
 */
#include "Arduino.h"
#include "ToggleButton.h"
#include "Interface.h"
#include "RotaryEncoderPosition.h"
#include "TemperatureSensor.h"
#include "Thermocycler.h"

#define DEBUG

/* Interface */
# define togglePin 20
# define statePin 19
ToggleButton toggleButton(togglePin, false, 300);
ToggleButton stateButton(statePin, false, 300);
RotaryEncoderPosition encoder(2, 3);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // RS E D4 D5 D6 D7
Cycles cycle;
Interface interface(&lcd, &cycle);

/* Temperature Control */
TemperatureSensor temperatureSensor(48, 50, 52);
Thermocycler thermocycler(46, 44, 42);


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

void fail() {
    interface.printErrorMessage();
    thermocycler.fail();
    exit(-1);
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

inline void doInterface() {
    while (!stateButton.isOn()) { // Get User Settings
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
}

inline void startCycle() {
    lcd.clear();
    unsigned long timeStart = millis();
    double goalTemperature = cycle.getTemperature(0);
    double currentTemperature = temperatureSensor.currentTemperature();

    while (stateButton.isOn() && !cycle.isFinished()) { // Run Thermocycle
        unsigned long time = millis() - timeStart;

        if (currentTemperature >= DANGER_TEMPERATURE) {
            fail();    
        }
        short cycleNum = cycle.setGoalTemperatureAndGetCycle(time,
                                                             &goalTemperature,
                                                             currentTemperature);
        double predicted = thermocycler.adjustTemperature(currentTemperature,
                                                          goalTemperature, time);

        interface.displayCycleInfo(cycleNum, cycle.getTimeSinceStart(), goalTemperature, currentTemperature);
        #if defined(DEBUG)
        double rate = thermocycler.queue.getTemperatureRate();
        Serial.print(time);
        Serial.print(",");
        Serial.print(currentTemperature);
        Serial.print(",");
        Serial.print(rate, 8);
        Serial.print(",");
        Serial.println(predicted);
        #endif
    }

    while (stateButton.isOn() && currentTemperature >= MIN_TEMPERATURE) {
        unsigned long time = millis() - timeStart;
        thermocycler.adjustTemperature(currentTemperature, MIN_TEMPERATURE, time);
        currentTemperature = temperatureSensor.currentTemperature();
        if (currentTemperature >= DANGER_TEMPERATURE) {
            fail();
        }
        interface.displaySetCycleInfo(currentTemperature, MIN_TEMPERATURE, false);
    }

    if (cycle.isFinished()) {
        stateButton.setOff();
    }
}

void loop() {
    thermocycler.reset();
    interface.reset();
    cycle.reset();

    doInterface();
    startCycle();
}
