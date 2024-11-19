#include "WasteDetector.h"

/*
* Constructor.
*/
WasteDetector::WasteDetector(int trig, int echo) {
    triggerPin=trig;
    echoPin=echo;
    currentState=EMPTY;
}

/*
* Method to initialize the proximity sensor.
*/
void WasteDetector::begin() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

/*
* Method to get the distance.
*/
long WasteDetector::getDistance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    return pulseIn(echoPin, HIGH) / 58;
}

/*
* Method to get the state.
*/
binState WasteDetector::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void WasteDetector::setState(binState newState) {
    currentState=newState;
}

