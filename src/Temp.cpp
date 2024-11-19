#include "Temp.h"

/*
* Constructor.
*/
Temp::Temp(int p) {
    pin=p;
    currentState = OKAY;
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