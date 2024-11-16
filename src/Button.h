#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button{

private:
    int pin;
    bool lastState = LOW;

public:
    Button(int p) {
        pin = p;
    }

    void begin() {
        pinMode(pin, INPUT);
    }

    bool isPressed() {
        bool currentState = digitalRead(pin);
        if(currentState == HIGH && lastState == LOW) {
            lastState = HIGH;
            return true;
        }
        lastState = currentState;
        return false;
    }
}

#endif 