#include "ServoMotor.h"

ServoMotor::ServoMotor(int p) {
    pin=p;
}

void ServoMotor::begin() {
    servo.attach(pin);
    setAngle(0);
}

void ServoMotor::setAngle(int angle) {
    servo.write(angle);
}

void ServoMotor::open() {
    setAngle(90);
}

void ServoMotor::close() {
    setAngle(0);
}

void ServoMotor::reverse() {
    setAngle(-90);
}
