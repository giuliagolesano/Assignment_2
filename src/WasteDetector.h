#ifndef WASTEDETECTOR_H
#define WASTEDETECTOR_H

#include <Arduino.h>

class WasteDetector {

private:
    int triggerPin;
    int echoPin;

public:
    WasteDetector(int trig, int echo) {
        triggerPin=trig;
        echoPin=echo;
    }

    void begin() {
        pinMode(triggerPin, OUTPUT);
        pinMode(echoPin, INPUT);
    }

    long getDistance() {
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
        return pulseIn(echoPin, HIGH) / 58;
    }
};

#endif


