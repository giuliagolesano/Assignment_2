#include "Pir.h"

Pir::Pir(int p) {
    pin=p;
}

void Pir::begin() {
    pinMode(pin,INPUT);
}

bool Pir::isUserDetected() {
    return digitalRead(pin) == HIGH;
}