Assignment 2 of the university course internet of things, we want to realise an embedded system called Smart Waste Disposal Container(dangerous liquid waste in particular). 

Hardware components:
    USER DETECTOR is a PIR, to detect the presence of a user in front of the container
    WASTE DETECTOR is a sonar, to measure how much the container is full
    DOOR is a servo-motor, controlling a small door, to enter waste
    USER LCD is a I2C LCD, used to interact with users
    OPEN and CLOSE are two tactile buttons
    L1 is a green led, to signal when the system is available working normally, L2 is a red led, to signal when the system is not available.
    TEMP is an analog temperature sensor 

The embedded subsystem is meant to communicate by means of the serial line with a PC, running a program called OPERATOR DASHBOARD (for operators). In particular the OPERATOR DASHBOARD is  a GUI application providing features to:
track and monitor the state of the container 
level of waste
temperature
a EMPTY button to empty the container
a RESTORE button to restore the container (in the case of alarm)


Description 

Basic behaviour: a user can dispose of some waste (liquid in particular) by pressing the OPEN button. This opens the DOOR, so that the user can enter (spill) the waste, pressing the CLOSE button to close the DOOR.  When/if the container becomes full, it is no longer available for accepting waste and it waits for being emptied by operators. 


