#ifndef WASTEDETECTORTASK_H
#define WASTEDETECTORTASK_H

#include <Arduino.h>
#include "Task.h"

enum binState {
    EMPTY,
    FILLING,
    FULL,
    EMPTYING
};

class WasteDetectorTask : public Task{

private:
    int triggerPin;
    int echoPin;
    binState currentState;
    bool isFull;

public:
    WasteDetectorTask(int trig, int echo);
    
    void init();
    void tick();

    binState getState();
    void setState(binState newState);

    long getDistance();
    bool isfull();
    void control();
};

#endif


