#ifndef USERDETECTIONTASK_H
#define USERDETECTIONTASK_H

#include <Arduino.h>
#include "Task.h"

enum PirState {
    PRESENT,
    ABSENCE
};

class UserDetectionTask : public Task{

private: 
    int pin;
    PirState currentState;
    bool userDetected;

public:
    UserDetectionTask(int p);

    PirState getState();
    void setState(PirState newState);

    void init();
    void tick();
    
    bool isUserDetected();
};

#endif