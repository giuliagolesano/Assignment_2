#include "UserDetectionTask.h"

/*
* Constructor.
*/
UserDetectionTask::UserDetectionTask(int p) {
    this->pin=p;
    this->currentState = PRESENT;
    this->userDetected = true;
}

/*
* Method to initialize the pir sensor.
*/
void UserDetectionTask::init() {
    pinMode(pin,INPUT);
}

void UserDetectionTask::tick() {
    if(digitalRead(pin) == HIGH) {
        userDetected = true;
        setState(PRESENT);
    }else{
        userDetected = false;
        setState(ABSENCE);
    }
}

/*
* Method to set the state.
*/
void UserDetectionTask::setState(PirState newState) {
    currentState = newState;
}

/*
* Method to get the state.
*/
PirState UserDetectionTask::getState() {
    return currentState;
}

/*
* Method to capture the present of a user.
*/
bool UserDetectionTask::isUserDetected() {
    return userDetected;
}