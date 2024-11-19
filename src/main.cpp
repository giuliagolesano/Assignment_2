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
unsigned long tsleep = 10000;
unsigned long time;
unsigned long T1 = 3000;
unsigned long T2 = 1000;
bool sleep = false;

void available();
void wakeUp();
void enterSleep();

void setup() {
  Serial.begin(9600);

  openButton.begin();
  closeButton.begin();
  greenLed.begin();
  redLed.begin();
  door.begin();
  pir.begin();
  wastedet.begin();
  temp.begin();
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);

  available();
  startTime = millis();

  enableInterrupt(7, wakeUp, RISING);
}

void loop() {
  /*
  if(pir.isUserDetected()){
    if(sleep) {
      wakeUp();
    }
    startTime = millis();
  }else{
    if(millis() - startTime >= tsleep){
      enterSleep();
    }
  }*/

 if(openButton.isPressed() && !wastedet.isfull() && pir.isUserDetected() && !temp.isDanger()) {
  door.open();
  door.setState(DOOR_OPENING);

  lcd.setCursor(0,0);
  lcd.print("PRESS CLOSE WHEN DONE");
  time = millis();
  door.setState(DOOR_OPEN);

  if(closeButton.isPressed() || (millis() - time >= T1) || wastedet.isfull() || temp.isDanger()) {
    door.close();
    door.setState(DOOR_CLOSING);

    if(wastedet.isfull()) {
      lcd.setCursor(0,0);
      lcd.print("CONTAINER FULL");
      greenLed.off();
      redLed.on();
    }else if(temp.isDanger()){
      lcd.setCursor(0,0);
      lcd.print("PROBLEM DETECTED");
      greenLed.off();
      redLed.on();
    }else{
      lcd.setCursor(0,0);
      lcd.print("WASTE RECEIVED");
      delay(T2);
      door.setState(DOOR_CLOSED);
    }
  }
 }
}

void available() {
  greenLed.on();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("PRESS OPEN TO ENTER WASTE");
  delay(2000);
}

void enterSleep() {
  sleep = true;

  lcd.clear();
  lcd.noBacklight();

  if(greenLed.isOn()) {
    redLed.off();
  }else if(redLed.isOn()) {
    greenLed.off();
  }

  Serial.flush();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  sleep_disable();
}

void wakeUp() {
  sleep = false;

  lcd.backlight();
  available();
}