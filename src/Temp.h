#ifndef TEMP_H
#define TEMP_H

#include <Arduino.h>

enum TempState {
    OKAY,
    DANGER,
    RESTORE
};

class Temp {

private: 
    int pin;
    TempState currentState;

public: 
    Temp(int p);
    void begin();
    float getTemperature();
    TempState getState();
    void setState(TempState newState);
};

#endif