#ifndef WASTEDETECTOR_H
#define WASTEDETECTOR_H

#include <Arduino.h>

unsigned long D1 

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
    bool isfull();
};

#endif


