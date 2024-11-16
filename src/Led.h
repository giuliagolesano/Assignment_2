#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {

    private int pin;

public:
    Led(int p) {
        pin=p;
    }

    void begin() {
        pinMode(pin,OUTPUT);
        off();
    }

    void on() {
        digitalWrite(pin, HIGH);
    }

    void off() {
        digitalWrite(pin,LOW);
    }

    void change() {
        digitalWrite(pin, !digitalRead(pin));
    }

};

#endif