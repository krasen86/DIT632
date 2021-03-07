/* ====================================
File name: exerc_6_4.c (or cpp)
Date: 2021-03-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 4542
====================================== */

// Include section
#include "stdio.h"
#include <sys/time.h>
#include <pthread.h>

// Define section
#define UPPER_TIME_BOUND 50 // Upper time limit to run the program
#define DISPLAY_SYSTEM_TIME "System time: %d\n" //  String to be printed to demonstrate the system time to the user via terminal
#define READING_PORT_MESSAGE "Reading value now...\n" // String to be printed for simulating the "reading input" functionality
#define SECONDS_TO_MILLISECONDS 1000 // Value used to represent 1 second in milliseconds
#define READ_IN_PORT_DELAY 5.0 // Delay in seconds for the simulation of reading input intervals
#define TIME_DELAY 1.0 // Delay in seconds for the system time

/* ==================================== Main program section ====================================== */
/* This program demonstrates the control of events while executing two threads in order to run two
 * different "processes" concurrently, by having access though to a commonly accessed, global system
 * time variable. Specifically, it is simulated to read an input every 5 seconds, by just printing it
 * currently in the terminal.
 * */

// Global variables
int programTime = 0; // Global variable to represent the runtime of the program

//Function declaration
void *timeCount(void *param); // define function used for the timeCount thread
void *readInPort(void *param); // define function used for the readInPort thread
double getTimeInMilliSeconds(); // define function used for getting the time in milliseconds

int main(){
    pthread_t timeCountThreadId; // declaration of the thread used to process the time counting functionality
    pthread_t readInPortThreadId; // declaration of the thread used to process the simulation of the reading input
    pthread_attr_t attr; // declaration of the thread attribute
    int previousTime = programTime; // initialization of the variable used to store the previous "execution time" of the program

    pthread_attr_init(&attr); // initialization of the thread attribute
    pthread_create(&timeCountThreadId, &attr, timeCount, NULL); // creation of the thread responsible to handle the time counting part, with the corresponding parameters (by passing the thread id, the thread parameters, the function that the thread will execute, and NULL as for we don't need to pass any parameters to the calling function)
    pthread_create(&readInPortThreadId, &attr, readInPort, NULL); // creation of the thread responsible to handle the input reading, with the corresponding parameters (by passing the thread id, the thread parameters, the function that the thread will execute, and NULL as for we don't need to pass any parameters to the calling function)

    // Main loop to check if the program time has not exceeded the upper time bound
    while ( programTime < UPPER_TIME_BOUND) {
        if (programTime == previousTime + TIME_DELAY && programTime < UPPER_TIME_BOUND) { // check if there has a TIME_DELAY time has passed since the previous execution time and whether it is still under the upper bounds
            printf(DISPLAY_SYSTEM_TIME, programTime); // print the runtime of the program
            previousTime = programTime; // set the previous time to the program time, used for the next iteration calculations
        }
    }

    return 0; // exit the program
}

// Thread function used to process the time counting related functionality
void *timeCount(void *param) {
    // Variable declaration
    double previousTime =  getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS; // store the previous time used to compare to the current program time, in order to see whether a `TIME_DELAY` of seconds have passed since the previous time

    while ( programTime < UPPER_TIME_BOUND){ // iterate until the upper time bounds have been reached
        if ( getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS == previousTime + TIME_DELAY) { // check if there has a `TIME_DELAY` of seconds have passed since the previous time
            programTime++; // increment program time by one second
            previousTime = getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS; // set the previous time to the current time in seconds
        }

    }

    pthread_exit(0); // exit the thread
}

// Thread function used to process the simulation of the input reading functionality of the program
void *readInPort(void *param) {
    double previousTime =  getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS; // store the previous time used to compare to the current program time, in order to see whether a `READ_IN_PORT_DELAY` of seconds have passed since the previous time

    while (programTime < UPPER_TIME_BOUND){ // iterate until the upper time bounds have been reached
        if ( getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS == previousTime + READ_IN_PORT_DELAY) { // check if there has a `READ_IN_PORT_DELAY` of seconds have passed since the previous time
            printf(READING_PORT_MESSAGE); // print a reading input related message to the terminal
            previousTime = getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS; // // set the previous time to the current time in seconds
        }
    }
    pthread_exit(0); // exit the thread
}

// Function to return the current time in milliseconds
double getTimeInMilliSeconds(){
    struct timeval currentTime; // declaration of a structure of type timeval
    gettimeofday(&currentTime, NULL); // get the system's clock time, expressed in seconds and microseconds as a difference since UNIX Epoch
    double currentTimeInMicroSeconds = currentTime.tv_sec + (currentTime.tv_usec / 1000000.0); // calculate the current time in micro seconds, by accessing the structure's parameters (i.e. tv_sec used for seconds since UNIX Epoch and tv_usec for the additional microseconds after the previous seconds' calculation since Unix Epoch)
    return (currentTimeInMicroSeconds) * 1000.0; // return the current time in milli seconds
}