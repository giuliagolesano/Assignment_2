#include "Button.h"

Button::Button(int p) {
    pin = p;
    lastState = LOW;
}

void Button::begin() {
    pinMode(pin, INPUT);
}

bool Button::isPressed() {
    bool currentState = digitalRead(pin);
    if(currentState == HIGH && lastState == LOW) {
        lastState = HIGH;
        return true;
    }
    lastState = currentState;
    return false;
}
