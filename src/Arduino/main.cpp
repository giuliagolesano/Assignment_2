#include <Arduino.h>
#include <avr/sleep.h>
#include <TimerOne.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>

#include "ButtonTask.h"
#include "LedTask.h"
#include "DoorTask.h"
#include "UserDetectionTask.h"
#include "WasteDetectorTask.h"
#include "TempTask.h"

#define EMPTY_COMMAND "EMPTY"
#define RESTORE_COMMAND "RESTORE"

ButtonTask* openButton;
ButtonTask* closeButton;
LedTask* greenLed;
LedTask* redLed;
DoorTask* door;
UserDetectionTask* pir;
WasteDetectorTask* wastedet;
TempTask* temp;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

unsigned long startTime;
unsigned long tsleep = 10000;
unsigned long time;
unsigned long T1 = 3000;
unsigned long T2 = 1000;
unsigned long T3 = 5000;
bool sleep = false;

void available();
void wakeUp();
void enterSleep();

void setup() {
    Serial.begin(9600);

    openButton = new ButtonTask(2);
    closeButton = new ButtonTask(3); 
    greenLed = new LedTask(10); 
    redLed = new LedTask(9);
    door = new DoorTask(8);
    temp = new TempTask(A0); 
    pir = new UserDetectionTask(7);
    wastedet = new WasteDetectorTask(5,6);

    openButton->init();
    closeButton->init();
    greenLed->init();
    redLed->init();
    door->init();
    temp->init();

    lcd.init();
    lcd.backlight();
    lcd.begin(20, 4);

    available();
    startTime = millis();

    enableInterrupt(7, wakeUp, RISING);
}

void loop() {
    temp->tick();
    wastedet->tick();

    Serial.print("TEMP:");
    Serial.print(temp->getTemperature());
    Serial.print(";WASTE:");
    Serial.println(wastedet->getDistance());

    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == EMPTY_COMMAND && wastedet->isfull()) {
            door->reverse();
            Serial.println("ACTION:EMPTY_EXECUTED");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("EMPTYING");
            delay(T3);
            available();
            wastedet->setState(EMPTY);
        } else if (command == RESTORE_COMMAND && temp->isDanger()) {
            Serial.println("ACTION:RESTORE_EXECUTED");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("RESTORING");
            delay(T3);
            available();
            temp->setState(OKAY);
        }
    }

    if (pir->isUserDetected()) {
        if (openButton->isPressed() && !wastedet->isfull() && !temp->isDanger()) {
            door->open();
            wastedet->setState(FILLING);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PRESS CLOSE WHEN DONE");
            time = millis();

            if (closeButton->isPressed() || (millis() - time >= T1) || wastedet->isfull() || temp->isDanger()) {
                door->close();

                if (wastedet->isfull()) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("CONTAINER FULL");
                    greenLed->off();
                    redLed->on();
                } else if (temp->isDanger()) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("PROBLEM DETECTED");
                    greenLed->off();
                    redLed->on();
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
    greenLed->on();
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

    if (greenLed->isOn()) {
        redLed->off();
    } else if (redLed->isOn()) {
        greenLed->off();
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
