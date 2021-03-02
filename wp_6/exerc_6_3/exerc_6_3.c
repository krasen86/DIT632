#include <stdio.h>
#include <time.h>

#define ML13_Status 0x0B10 // Mock status reading from system
#define ML13_Control 0x0B00 // Mock control reading
#define TRUE 1  // Define boolean true
#define FALSE 0 // Define boolean false
#define CLOSE_DOOR 0x0B10 // Hexadecimal value for setting control value to close the door
#define OPEN_DOOR 0x0B01  // Hexadecimal value for setting control value to open door
#define DEFAULT_DELAY 5 // Default delay time used in the system

/* ==================================== Main program section ====================================== */
/* This program is used as a subsystem for an automatic door in order to do the logical thinking of how an automatic
 * door should work. The program takes the status of the system in order to see if the sensor gets a reading in order to start
 * the process of opening the door. When the door opening routine starts, the program set the control value for opening a door
 * in the control register for the system to 1 and then loops to wait until the system has set the value in the status for
 * DOOR_WIDE_OPEN to 1. The program then sets a delay for DEFAULT_DELAY(5) seconds time to keep the door open. After the delay
 * the program will set the control value for close door in the control register in order to initialize the closing door routine.
 * If a door is already open when the sensor gets a reading, the delay will be started again with DEFAULT_DELAY(5) seconds
 * and will then initialize the closing of the door afterwards.
 */

int isDoorOpen(); // Function to check the binary status if door is open or not, returns true or false
void delay(int time); // Delay function using clock(); from time.h to be able to delay by seconds
void closeDoor(); // Function to set the binary status code for the control registry to close door
void openDoor(); // Function to set the binary status code for the control registry to open door
unsigned int getStatus(); // Gets the current status of the system (mocked in our case with ML13_Status)

unsigned int status; // Used to keep track of the status registry binary
unsigned int control; // Used to keep track of the control registry binary

int main () {
    closeDoor(); // Initialize by having the door closed
    while(1){
        status = getStatus(); // Get the status from the status register
        if(status & 0b1000) { // Bitwise and to check the value in status that has the sensor, is true if something is detected
            if(isDoorOpen()){ // Check if door is open to just restart delay
                delay(DEFAULT_DELAY); // set the delay
                closeDoor(); // After delay, close the door
            }else{ // Else if door is closed
                openDoor(); // Set the control value of open door to 1
                while(!isDoorOpen()); // Wait for the system to open the door
                delay(DEFAULT_DELAY); // Set the delay to keep door open for 5 seconds
                closeDoor(); // set the control value of close door to 1
            }
        }
    }
}

unsigned int getStatus(){
    return ML13_Status; // Mocking the  status of the system by returning ML13_status
}

int isDoorOpen(){
    if(status & 0B10000){ //Bitwise and in order to check the bit value for an open door in the status register
        return TRUE; // Return true if door is open
    }else{
        return FALSE; //Return false otherwise
    }
}

void closeDoor(){
    control = CLOSE_DOOR; // Setting the control value of the control register for closing door to 1
}

void openDoor(){
    control = OPEN_DOOR; // Setting the control value of the control register for opening the door to 1
}

void delay(int time){
    clock_t currentTime = 0; // initialize typedef clock_t currentTime to 0
    clock_t startTime = clock() / CLOCKS_PER_SEC;   // initialize typedef clock_t startTime to the current processor time / CLOCKS_PER_SEC
                                                    // to be able to calculate the current time in seconds
    while (currentTime < startTime + time){ // Checking until we reach the desired end time by adding our desired time to wait to the startTime
        currentTime = clock() / CLOCKS_PER_SEC; // set the currentTime to current processor time / CLOCKS_PER_SEC to get the current time in seconds
    }
}