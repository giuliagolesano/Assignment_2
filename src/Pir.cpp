#include "Pir.h"

/*
* Constructor.
*/
Pir::Pir(int p) {
    pin=p;
    currentState = PRESENT;
}

/*
* Method to initialize the pir sensor.
*/
void Pir::begin() {
    pinMode(pin,INPUT);
}

/*
* Method to set the state.
*/
void Pir::setState(PirState newState) {
    currentState = newState;
}

/*
* Method to get the state.
*/
void Pir::getState() {
    return currentState;
}

/*
* Method to capture the present of a user.
*/
bool Pir::isUserDetected() {
    if(digitalRead(pin) == HIGH && currentState == ABSENCE){
        setState(PRESENT);
    }
    if(digitalRead(pin) == LOW && currentState == PRESENT){
        setState(ABSENCE);
    }
}