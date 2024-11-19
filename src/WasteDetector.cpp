#include "WasteDetector.h"

int D1 =300;
const float vs = 331.5 + 0.6*20;

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

    digitalWrite(triggerPin,LOW);
    delayMicroseconds(3);
    digitalWrite(triggerPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin,LOW);

    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;

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

bool WasteDetector::isfull() {
    if(getDistance() <= D1) {
        setState(FULL);
        return true;
    }else{
        return false;
    }
}

