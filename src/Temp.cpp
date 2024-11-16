#include "Temp.h"

class Temp {

    private int pin;

public: 
    Temp(int p) {
        pin=p;
    }

    void begin() {
        pinMode(pin, INPUT);
    }

    float getTemperature() {
        int rawValue = analogRead(pin);
        float voltage = rawValue * (5.0 / 1023.0);
        return (voltage - 0.5) * 100;
    }
}