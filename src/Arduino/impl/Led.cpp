#include "Led.h"

/*
* Constructor.
*/
Led::Led(int p) {
    pin=p;
}

/*
* Method to initialize the led.
*/
void Led::begin() {
    pinMode(pin,OUTPUT);
    off();
}

/*
* Method to set the led on.
*/
void Led::on() {
    digitalWrite(pin, HIGH);
}

/*
* Method to set the led off.
*/
void Led::off() {
    digitalWrite(pin,LOW);
}

/*
* Method to change the led on/off.
*/
void Led::change() {
    digitalWrite(pin, !digitalRead(pin));
}

bool Led::isOn() {
    return digitalRead(pin) == HIGH;
}