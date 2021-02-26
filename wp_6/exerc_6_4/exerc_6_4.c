/* ====================================
File name: exerc_x_x.c (or cpp) TODO update exercise number
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include "stdio.h"
#include <sys/time.h>
#include <pthread.h>

// Define section
#define UPPER_TIME_BOUND 50
#define DISPLAY_SYSTEM_TIME "System time: %d\n"
#define READING_PORT_MESSAGE "Reading value now...\n"
#define SECONDS_TO_MILLISECONDS 1000
#define READ_IN_PORT_DELAY 5.0
#define TIME_DELAY 1.0
/* ==================================== Main program section ====================================== */
/* This program TODO..... */

// Global variables
int programTime = 0;

//Function declaration
void *timeCount(void *param);
void *readInPort(void *param);
double getTimeInMilliSeconds();

int main(){
    pthread_t timeCountThreadId;
    pthread_t readInPortThreadId;
    pthread_attr_t attr;
    int previousTime = programTime;

    pthread_attr_init(&attr);
    pthread_create(&timeCountThreadId, &attr, timeCount, NULL);

    pthread_create(&readInPortThreadId, &attr, readInPort, NULL);


    while ( programTime < UPPER_TIME_BOUND){

        if (programTime == previousTime + TIME_DELAY && programTime < UPPER_TIME_BOUND) {
            printf(DISPLAY_SYSTEM_TIME, programTime);
            previousTime = programTime;
        }
    }
    return 0;
}

// Thread functions
void *timeCount(void *param) {
    double previousTime =  getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS;

    while ( programTime < UPPER_TIME_BOUND){
        if ( getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS == previousTime + TIME_DELAY) {
            programTime++;
            previousTime = getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS;
        }

    }

    pthread_exit(0);
}

void *readInPort(void *param) {
    double previousTime =  getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS;

    while (programTime < UPPER_TIME_BOUND){
        if ( getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS == previousTime + READ_IN_PORT_DELAY) {
            printf(READING_PORT_MESSAGE);
            previousTime = getTimeInMilliSeconds()/SECONDS_TO_MILLISECONDS;
        }
    }
    pthread_exit(0);
}

double getTimeInMilliSeconds(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}