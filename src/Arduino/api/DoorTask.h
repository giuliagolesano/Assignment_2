#ifndef DOORTASK_H
#define DOORTASK_H

#include <Arduino.h>
#include <Servo.h>
#include "Task.h"


enum DoorState {
    DOOR_CLOSED,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING,
    DOOR_REVERSING
};

class DoorTask : public Task{

private:
    Servo servo;
    int pin;
    DoorState currentState;

public:
    DoorTask(int pin);

    void init() override;
    void tick() override;

    DoorState getState();
    void setState(DoorState newState);

    void setAngle(int angle);
    void open();
    void close();
    void reverse();
};

#endif