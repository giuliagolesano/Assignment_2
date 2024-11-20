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

#define EMPTY_COMMAND "EMPTY"
#define RESTORE_COMMAND "RESTORE"

Button openButton(2);
Button closeButton(3);
Led greenLed(10);
Led redLed(9);
ServoMotor door(8);
Pir pir(7);
WasteDetector wastedet(5, 6);
Temp temp(A0);

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

unsigned long startTime;
unsigned long tsleep = 10000;
unsigned long time;
unsigned long T1 = 3000;
unsigned long T2 = 1000;
unsigned long T3 = 5000;
bool sleep = false;
bool emptyButton = false;
bool restoreButton = false;

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
    lcd.begin(20, 4);

    available();
    startTime = millis();

    enableInterrupt(7, wakeUp, RISING);
}

void loop() {
    temp.control();
    wastedet.control();

    Serial.print("TEMP:");
    Serial.print(temp.getTemperature());
    Serial.print(";WASTE:");
    Serial.println(wastedet.getLevel());

    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == EMPTY_COMMAND && wastedet.isfull()) {
            door.reverse();
            Serial.println("ACTION:EMPTY_EXECUTED");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("EMPTYING");
            delay(T3);
            available();
            wastedet.setState(EMPTY);
        } else if (command == RESTORE_COMMAND && temp.isDanger()) {
            Serial.println("ACTION:RESTORE_EXECUTED");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("RESTORING");
            delay(T3);
            available();
            temp.setState(OKAY);
        }
    }

    // Logica esistente per sleep e gestione della porta
    if (pir.isUserDetected()) {
        if (openButton.isPressed() && !wastedet.isfull() && !temp.isDanger()) {
            door.open();
            wastedet.setState(FILLING);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PRESS CLOSE WHEN DONE");
            time = millis();

            if (closeButton.isPressed() || (millis() - time >= T1) || wastedet.isfull() || temp.isDanger()) {
                door.close();

                if (wastedet.isfull()) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("CONTAINER FULL");
                    greenLed.off();
                    redLed.on();
                } else if (temp.isDanger()) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("PROBLEM DETECTED");
                    greenLed.off();
                    redLed.on();
                } else {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("WASTE RECEIVED");
                    delay(T2);
                    available();
                }
            }
        }
    } else {
        if (millis() - startTime >= tsleep) {
            enterSleep();
        }
    }
}

void available() {
    greenLed.on();
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("PRESS OPEN TO ENTER WASTE");
    delay(2000);
}

void enterSleep() {
    sleep = true;

    lcd.clear();
    lcd.noBacklight();

    if (greenLed.isOn()) {
        redLed.off();
    } else if (redLed.isOn()) {
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
