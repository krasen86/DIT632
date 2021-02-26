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


    while ( programTime < 50){
        if (programTime == previousTime + 1) {
            printf("System time: %d\n", programTime);
            previousTime = programTime;
        }
    }
}

// Thread functions
void *timeCount(void *param) {
    double previousTime =  getTimeInMilliSeconds();

    while ( programTime < 50){
        if ( getTimeInMilliSeconds() == previousTime + 1) {
            programTime++;
            previousTime = getTimeInMilliSeconds();
        }

    }

    pthread_exit(0);
}

void *readInPort(void *param) {
    double previousTime =  getTimeInMilliSeconds();

    while (programTime<50){
        if ( getTimeInMilliSeconds() == previousTime + 5) {
            printf("Reading value now...");
            previousTime = getTimeInMilliSeconds();
        }
    }
    pthread_exit(0);
}

double getTimeInMilliSeconds(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec + (t.tv_usec / 1000000.0)) * 1000.0;
}