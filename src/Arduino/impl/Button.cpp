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
    if(digitalRead(pin) == HIGH) return true;
    else return false;
}
