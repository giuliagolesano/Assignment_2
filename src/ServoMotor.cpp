#include "ServoMotor.h"

/*
* Constructor.
*/
ServoMotor::ServoMotor(int p) {
    pin=p;
    currentState = DOOR_CLOSED;
}

/*
* Method to initialize the servo motor.
*/
void ServoMotor::begin() {
    servo.attach(pin);
    setAngle(0);
}

/*
* Method to set the angle of the servo motor.
*/
void ServoMotor::setAngle(int angle) {
    servo.write(angle);
}

/*
* Method to open the door.
*/
void ServoMotor::open() {
    if(currentState == DOOR_CLOSED || currentState == DOOR_CLOSING){
        currentState = DOOR_OPENING;    
        setAngle(90);
        currentState = DOOR_OPEN;
    }

}

/*
* Method to close the door.
*/
void ServoMotor::close() {
    if(currentState == DOOR_OPEN || currentState == DOOR_OPENING){
        currentState = DOOR_CLOSING;
        setAngle(0);
        currentState = DOOR_CLOSED;
    }
}

/*
* Method to reverse the door and empty the waste disposal system.
*/
void ServoMotor::reverse() {
    if(currentState == DOOR_CLOSED || currentState == DOOR_OPEN){
        currentState = DOOR_REVERSING;
        setAngle(180);
        delay(1000)
        currentState = DOOR_CLOSED;
    }
}

/*
* Method to get the state.
*/
DoorState ServoMotor::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void ServoMotor::setState(DoorState newState) {
    currentState = newState;
}

/*
* Method to .
*/
void ServoMotor::update() {

}
