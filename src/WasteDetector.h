#ifndef WASTEDETECTOR_H
#define WASTEDETECTOR_H

#include <Arduino.h>

enum binState {
    EMPTY,
    FILLING,
    FULL,
    EMPTYING
};

class WasteDetector {

private:
    int triggerPin;
    int echoPin;
    binState currentState;

public:
    WasteDetector(int trig, int echo);
    void begin();
    binState getState();
    void setState(binState newState);
    long getDistance();
};

#endif


