#include <Arduino.h>
#include <avr/sleep.h>
#include <TimerOne.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>

#include "Button.h"
#include "Led.h"
#include "ServoMotor.h"
#include "Pir.h"
#include "WasteDetector.h"
#include "Temp.h"

// put function declarations here:
//int myFunction(int, int);

Button openButton(2);
Button closeButton(3);
Led greenLed(10);
Led redLed(9);
ServoMotor door(8);
Pir pir(7);
WasteDetector wastedet(5,6);
Temp temp(A0);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

unsigned long startTime;

void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  Serial.begin(9600);

  openButton.begin();
  closeButton.begin();
  greenLed.begin();
  redLed.begin();
  door.begin();
  pir.begin();
  wastedet.begin();
  temp.begin();

  //enableInterrupt(openButton, wakeUp, RISING);
  //enableInterrupt(closeButton, wakeUp, RISING);

  startTime = millis();

  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);

  //Timer1.initialize(1000000);
  //Timer1.attachInterrupt(ledManagement);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

/* put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}*/