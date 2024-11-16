#include "Temp.h"

Temp::Temp(int p) {
    pin=p;
}

void Temp::begin() {
    pinMode(pin, INPUT);
}

float Temp::getTemperature() {
    int rawValue = analogRead(pin);
    float voltage = rawValue * (5.0 / 1023.0);
    return (voltage - 0.5) * 100;
}