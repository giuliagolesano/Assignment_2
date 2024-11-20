#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <Servo.h>

enum DoorState {
    DOOR_CLOSED,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING,
    DOOR_REVERSING
};

class ServoMotor {

private:
    Servo servo;
    int pin;
    DoorState currentState;

public:
    ServoMotor(int pin);

    void begin();

    void update();
    DoorState getState();
    void setState(DoorState newState);

    void setAngle(int angle);
    void open();
    void close();
    void reverse();
};

#endif