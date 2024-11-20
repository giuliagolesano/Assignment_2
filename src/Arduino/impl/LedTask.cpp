#include "LedTask.h"
#include <Arduino.h>

/*
* Constructor.
*/
LedTask::LedTask(int p) {
    this->pin=p;
}

/*
* Method to initialize the led.
*/
void LedTask::init() {
    pinMode(pin,OUTPUT);
    off();
}

void LedTask::tick() {
    
}

/*
* Method to set the led on.
*/
void LedTask::on() {
    digitalWrite(pin, HIGH);
}

/*
* Method to set the led off.
*/
void LedTask::off() {
    digitalWrite(pin,LOW);
}

/*
* Method to change the led on/off.
*/
void LedTask::change() {
    digitalWrite(pin, !digitalRead(pin));
}

bool LedTask::isOn() {
    return digitalRead(pin) == HIGH;
}