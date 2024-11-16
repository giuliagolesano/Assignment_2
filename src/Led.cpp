#include "Led.h"

Led::Led(int p) {
    pin=p;
}

void Led::begin() {
    pinMode(pin,OUTPUT);
    off();
}

void Led::on() {
    digitalWrite(pin, HIGH);
}

void Led::off() {
    digitalWrite(pin,LOW);
}

void Led::change() {
    digitalWrite(pin, !digitalRead(pin));
}