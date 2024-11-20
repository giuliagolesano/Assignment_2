#include "TempTask.h"

#define MAXTEMP 40
#define MAXTEMPTIME 5000

/*
* Constructor.
*/
TempTask::TempTask(int p) {
    this->pin=p;
    this->currentState = OKAY;
    this->dangerStartTime = 0;
    this->currentTemperature = 0.0;
}

/*
* Method to initialize the temperature sensor.
*/
void TempTask::init() {
    pinMode(pin, INPUT);
}

/*
* Method to get the temperature.
*/
float TempTask::getTemperature() {
    return currentTemperature;
}

void TempTask::tick() {
    float currentTemp;
    int rawValue = analogRead(pin);
    float voltage = rawValue * (5.0 / 1023.0);
    currentTemperature = (voltage - 0.5) * 100;

    if (currentTemp > MAXTEMP) {
        if (dangerStartTime == 0) {
            dangerStartTime = millis();
        } else if (millis() - dangerStartTime >= MAXTEMPTIME) {
            setState(DANGER);
        }
    } else {
        dangerStartTime = 0;
        setState(OKAY);
    }
}

/*
* Method to get the state.
*/
TempState TempTask::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void TempTask::setState(TempState newState) {
    currentState = newState;
}

bool TempTask::isDanger() {
    return currentState == DANGER;
}