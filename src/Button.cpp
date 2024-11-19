#include "Button.h"

/*
* Constructor.
*/
Button::Button(int p) {
    pin = p;
    lastState = LOW;
}

/*
* Method to initialize the button.
*/
void Button::begin() {
    pinMode(pin, INPUT);
}

/*
* Method to capture the pression of the button.
*/
bool Button::isPressed() {
    bool currentState = digitalRead(pin);
    if(currentState == HIGH && lastState == LOW) {
        lastState = HIGH;
        return true;
    }
    lastState = currentState;
    return false;
}
