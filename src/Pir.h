#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class Pir{

    private int pin;

public:
    Pir(int p) {
        pin=p;
    }

    void begin() {
        pinMode(pin,INPUT);
    }

    bool isUserDetected() {
        return digitalRead(pin) == HIGH;
    }
};

#endif