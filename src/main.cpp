#include <Arduino.h>

#include "Button.h"
#include "Led.h"
#include "ServoMotor.h"

// put function declarations here:
//int myFunction(int, int);

Button openButton(2);
Button closeButton(3);
Led greenLed(9);
Led redLed(10);
ServoMotor door(8);

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  openButton.begin();
  closeButton.begin();
  greenLed.begin();
  redLed.begin();
  door.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}

/* put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}*/