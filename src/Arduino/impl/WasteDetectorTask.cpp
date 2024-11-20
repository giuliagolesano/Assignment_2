#include "WasteDetectorTask.h"

int D1 =300;
const float vs = 331.5 + 0.6*20;

/*
* Constructor.
*/
WasteDetectorTask::WasteDetectorTask(int trig, int echo) {
    this->triggerPin=trig;
    this->echoPin=echo;
    this->currentState=EMPTY;
}

/*
* Method to initialize the proximity sensor.
*/
void WasteDetectorTask::init() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    isFull = false;
}

/*
* Method to get the distance.
*/
long WasteDetectorTask::getDistance() {
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

void WasteDetectorTask::tick() {
    if(getDistance() <= D1) {
        setState(FULL);
        isFull = true;
    }
}

/*
* Method to get the state.
*/
binState WasteDetectorTask::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void WasteDetectorTask::setState(binState newState) {
    currentState=newState;
}

bool WasteDetectorTask::isfull() {
    return isFull;
}

