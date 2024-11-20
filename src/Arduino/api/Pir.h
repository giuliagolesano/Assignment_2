#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

enum PirState {
    PRESENT,
    ABSENCE
};

class Pir{

private: 
    int pin;
    PirState currentState;

public:
    Pir(int p);
    PirState getState();
    void setState(PirState newState);
    void begin();
    bool isUserDetected();
};

#endif