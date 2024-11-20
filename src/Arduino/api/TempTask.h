#ifndef TEMPTASK_H
#define TEMPTASK_H

#include <Arduino.h>
#include "Task.h"

enum TempState {
    OKAY,
    DANGER,
    RESTORE
};

class TempTask : public Task{

private: 
    int pin;
    TempState currentState;
    unsigned long dangerStartTime;
    float currentTemperature;

public: 
    TempTask(int p);

    void init() override;
    void tick() override;

    void setState(TempState newState);
    TempState getState();

    float getTemperature();
    bool isDanger();
    void control();
};

#endif