#ifndef WASTEDETECTOR_H
#define WASTEDETECTOR_H

#include <Arduino.h>

class WasteDetector {

private:
    int triggerPin;
    int echoPin;

public:
    WasteDetector(int trig, int echo);
    void begin();
    long getDistance();
};

#endif


