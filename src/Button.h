#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button{

private:
    int pin;
    bool lastState;

public:
    Button(int p);
    void begin();
    bool isPressed();
};

#endif
