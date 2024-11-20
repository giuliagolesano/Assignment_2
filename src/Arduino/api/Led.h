#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {

private: 
    int pin;

public:
    Led(int p);
    void begin();
    void on();
    void off();
    void change();
    bool isOn();
};

#endif