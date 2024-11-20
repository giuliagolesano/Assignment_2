#ifndef BUTTONTASK_H
#define BUTTONTASK_H

#include <Arduino.h>

#include "Task.h"

class ButtonTask : public Task{

private:
    int pin;
    bool lastState;

public:
    ButtonTask(int p);
    void init() override;
    void tick() override;
    bool isPressed();
};

#endif
