#include "ButtonTask.h"
#include <Arduino.h>

/*
* Constructor.
*/
ButtonTask::ButtonTask(int p) {
    this->pin = p;
    this->lastState = LOW;
}

/*
* Method to initialize the button.
*/
void ButtonTask::init() {
    pinMode(pin, INPUT);
}

void ButtonTask::tick() {
  lastState = (digitalRead(pin) == HIGH);
}

/*
* Method to capture the pression of the button.
*/
bool ButtonTask::isPressed() {
    return lastState;
}
