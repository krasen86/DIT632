/* ====================================
File name: exerc_6_5.c
Date: 2021-03-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 4542
====================================== */

// Include section
#include <stdio.h>
#include <pthread.h>

// Define section
#define MAX 10 // buffer size
#define MAIN_THREAD_PRINT "Main is executing\n" // notification for main thread is running
#define BUFFER_STORE_STRING "Buffer store\n" // notification for the put thread storing
#define BUFFER_OUTPUT_STRING "Buffer output: %c\n" // notification for the fetch thread outputting the letter
#define FIRST_LETTER 'a' // define first letter of alphabet
#define LAST_LETTER 'z' // define last letter of alphabet
#define THREAD_DELAY 3000000 // delay the running of the threads
#define MAIN_DELAY 5000000 // delay the running of the main method/thread


/* ==================================== Main program section ====================================== */
/* This program TODO .... */


pthread_mutex_t countMutex = PTHREAD_MUTEX_INITIALIZER; // define and initialize the mutex for controlling the thread
pthread_cond_t  notEmpty = PTHREAD_COND_INITIALIZER; // define the condition signal used for notifying the mutex for the status of the buffer and control the thread execution
pthread_cond_t  notFull = PTHREAD_COND_INITIALIZER; // define the condition signal used for notifying the mutex for the status of the buffer and control the thread execution

// Global buffer and corresponding counters.
char letter = FIRST_LETTER; //the starting letter
unsigned short count = 0; // used to count the number of letters in the buffer
char buffer[MAX]; // circular buffer
int nextInPosition = 0; // index for next character to be put in buffer (put)
int nextOutPosition = 0; // index for next character to be read ( fetch )

// Function declarations
void *put(void *param); // Thread function for populating the buffer with alphabetical values
void *fetch(void *param); // Thread function for printing from buffer
void wait(int loops); // wait function for delaying the printing

int main(void){
    pthread_t putThreadId; // define the thread pointer to store the id of the put thread
    pthread_t fetchThreadId; // define the thread pointer to store the id of the fetch thread
    pthread_attr_t attr; // attr structure to store the attributes for the initialization of the threads when created

    pthread_attr_init(&attr);  // initialize the attributes to default
    pthread_create(&putThreadId, &attr, put, NULL); // create thread assign the thread id to the pointer putThreadID, pass the default initialized attributes pointer, attach the function for populating the buffer to the thread and pass Null arguments to the function
    pthread_create(&fetchThreadId, &attr, fetch, NULL); // create thread assign the thread id to the pointer fetchThreadID, pass the default initialized attributes pointer, attach the function for printing the buffer to the thread and pass Null arguments to the function

    while(1){ // main loop
        wait(MAIN_DELAY); // delay running to not spam the console
        printf(MAIN_THREAD_PRINT); // notify that the main thread is running
    }

}
// Function to delay the running of the threads
void wait(int loops){
    int i = 0; // index set to 0
    while(i < loops) { // run delay loop for the desired amount of iteration
        i++; // increment loop control index
    }
}

// Thread function to populate the buffer
void *put(void *param){
    while(1){ // start thread loop
        pthread_mutex_lock(&countMutex); // call the mutex lock and pass the mutex("key") in order to lock the risk area while operating on a shared resources
        if(count > 0) { // check if there are elements in the buffer
            pthread_cond_wait(&notFull, &countMutex); // set a conditional wait for the thread until the not_full signal is signaled and pass the mutex
        }
        buffer[nextInPosition] = letter; // write a letter in the buffer
        printf(BUFFER_STORE_STRING); // notify that a letter has been stored in the buffer
        if (letter == LAST_LETTER) { // check if the letter has reached the last alphabetical letter
            letter = FIRST_LETTER; // set the letter to be the first letter of the alphabet
        } else { // base case
            letter++; // increment the letter
        }
        if (nextInPosition == MAX - 1) { // check if the nextPosition index has reached the last position in the array
            nextInPosition = 0; // reset the next position to point to the first position of the buffer
        } else { // base case
            nextInPosition++; // increment the nextPosition index
        }
        count++; // increment the count
        wait(THREAD_DELAY); // delay the run of the thread

        pthread_cond_signal(&notEmpty); // send a conditional signal to the threads that the buffer is not empty
        pthread_mutex_unlock(&countMutex); // call the mutex unlock and pass the mutex("key") in order to unlock the risk area
    }
}

// Thread function to read and display the elements from the buffer
void *fetch(void *param){
    while(1){ // thread loop
        pthread_mutex_lock(&countMutex); // call the mutex lock and pass the mutex("key") in order to lock the risk area while operating on a shared resources
        if(count == 0) { // check if buffer does not contain any letters
            pthread_cond_wait(&notEmpty, &countMutex); // send a conditional signal to the threads that the buffer is not empty
        }
        printf(BUFFER_OUTPUT_STRING, buffer[nextOutPosition]); // print out the next letter in the buffer
        if (nextOutPosition == MAX - 1) { //  check if the nextOutPosition index has reached the last position in the array
            nextOutPosition = 0; // reset the next position to point to the first position of the buffer
        } else {  // base case
            nextOutPosition++; // increment the nextOutPosition index
        }
        count--; // decrement the counter
        wait(THREAD_DELAY); // delay the run of the thread
        pthread_cond_signal(&notFull); // send a conditional signal to the threads that the buffer is not full

        pthread_mutex_unlock(&countMutex); // call the mutex unlock and pass the mutex("key") in order to unlock the risk area
    }
}
