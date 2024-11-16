#include "Pir.h"

class Pir{

    private int pin;

public:
    Pir(int p) {
        pin=p;
    }

    void begin() {
        pinMode(pin,INPUT);
    }

    bool isUserDetected() {
        return digitalRead(pin) == HIGH;
    }
}