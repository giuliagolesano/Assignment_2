#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <Servo.h>

class ServoMotor {

private:
    Servo servo;
    int pin;

public:
    ServoMotor(int p) {
        pin=p;
    }

    void begin() {
        servo.attach(pin);
        setAngle(0);
    }

    void setAngle(int angle) {
        servo.write(angle);
    }

    void open() {
        setAngle(90);
    }

    void close() {
        setAngle(0);
    }

    void reverse() {
        setAngle(-90);
    }
};

#endif