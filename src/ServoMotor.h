#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <Servo.h>

class ServoMotor {

private:
    Servo servo;
    int pin;

public:
    Temp(int pin);
    void begin();
    void setAngle(int angle);
    void open();
    void close();
    void reverse();
};

#endif