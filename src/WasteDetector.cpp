#include "WasteDetector.h"

WasteDetector::WasteDetector(int trig, int echo) {
    triggerPin=trig;
    echoPin=echo;
}

void WasteDetector::begin() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long WasteDetector::getDistance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    return pulseIn(echoPin, HIGH) / 58;
}

