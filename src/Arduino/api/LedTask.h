#ifndef LEDTASK_H
#define LEDTASK_H

#include <Arduino.h>
#include "Task.h"

class LedTask : public Task{

private: 
    int pin;

public:
    LedTask(int p);

    void init() override;
    void tick() override;

    void on();
    void off();
    void change();
    bool isOn();
};

#endif