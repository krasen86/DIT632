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

/* ==================================== Main program section ====================================== */
/* This program TODO..... */

int programTime = 0;
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

        if (programTime == previousTime + 1 && programTime < UPPER_TIME_BOUND) {
            printf("System time: %d\n", programTime);
            previousTime = programTime;
        }
    }

    return 0;
}

// Thread functions
void *timeCount(void *param) {
    double previousTime =  getTimeInMilliSeconds()/1000;

    while ( programTime < 50){
        if ( getTimeInMilliSeconds()/1000 == previousTime + 1.0) {
            programTime++;
            previousTime = getTimeInMilliSeconds()/1000;
        }

    }

    pthread_exit(0);
}

void *readInPort(void *param) {
    double previousTime =  getTimeInMilliSeconds()/1000;

    while (programTime < UPPER_TIME_BOUND){
        if ( getTimeInMilliSeconds()/1000 == previousTime + 5.0) {
            printf("Reading value now...\n");
            previousTime = getTimeInMilliSeconds()/1000;
        }
    }
    pthread_exit(0);
}

double getTimeInMilliSeconds(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}