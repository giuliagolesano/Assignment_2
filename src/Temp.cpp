#include "Temp.h"

#define MAXTEMP 40
#define MAXTEMPTIME 5000

/*
* Constructor.
*/
Temp::Temp(int p) {
    pin=p;
    currentState = OKAY;
    dangerStartTime = 0;
}

/*
* Method to initialize the temperature sensor.
*/
void Temp::begin() {
    pinMode(pin, INPUT);
}

/*
* Method to get the temperature.
*/
float Temp::getTemperature() {
    int rawValue = analogRead(pin);
    float voltage = rawValue * (5.0 / 1023.0);
    return (voltage - 0.5) * 100;
}

void Temp::control() {
    float currentTemp = getTemperature();

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
TempState Temp::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void Temp::setState(TempState newState) {
    currentState = newState;
}

bool Temp::isDanger() {
    return currentState == DANGER;
}