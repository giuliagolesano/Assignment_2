#include "DoorTask.h"

/*
* Constructor.
*/
DoorTask::DoorTask(int p) {
    this->pin=p;
    this->currentState = DOOR_CLOSED;
}

/*
* Method to initialize the servo motor.
*/
void DoorTask::init() {
    servo.attach(pin);
    setAngle(0);
}

void DoorTask::tick() {

}

/*
* Method to set the angle of the servo motor.
*/
void DoorTask::setAngle(int angle) {
    servo.write(angle);
}

/*
* Method to open the door.
*/
void DoorTask::open() {
    if(currentState == DOOR_CLOSED || currentState == DOOR_CLOSING){
        currentState = DOOR_OPENING;    
        setAngle(90);
        currentState = DOOR_OPEN;
    }

}

/*
* Method to close the door.
*/
void DoorTask::close() {
    if(currentState == DOOR_OPEN || currentState == DOOR_OPENING){
        currentState = DOOR_CLOSING;
        setAngle(0);
        currentState = DOOR_CLOSED;
    }
}

/*
* Method to reverse the door and empty the waste disposal system.
*/
void DoorTask::reverse() {
    if(currentState == DOOR_CLOSED || currentState == DOOR_OPEN){
        currentState = DOOR_REVERSING;
        setAngle(180);
        delay(1000);
        currentState = DOOR_CLOSED;
    }
}

/*
* Method to get the state.
*/
DoorState DoorTask::getState() {
    return currentState;
}

/*
* Method to set the state.
*/
void DoorTask::setState(DoorState newState) {
    currentState = newState;
}

