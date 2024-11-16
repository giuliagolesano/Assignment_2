#ifndef TEMP_H
#define TEMP_H

#include <Arduino.h>

class Temp {

private: 
    int pin;

public: 
    Temp(int p);
    void begin();
    float getTemperature();
};

#endif