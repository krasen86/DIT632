/* ====================================
File name: exerc_2_6.c (or cpp)
Date: 2021-02-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: 5202
====================================== */

// Include section
#include "stdio.h"

// Define section
#define MAX_SIZE_QUEUE 5 // max items to be stored in the queue
#define INITIAL_ITEM_VALUE -1 // used to initialize the queue
#define TRUE 1 // define boolean true
#define FALSE 0 // define boolean false
// For testing
#define INSERT_SUCCESSFUL "Insert %d in the queue. " // message to confirm insert to queue
#define INSERT_FAIL_QUEUE_IS_FULL "Requested to insert %d. Currently the queue is full. " // message for failed insertion in the queue
#define REMOVE_ITEM_SUCCESSFUL "Removed %d from the queue. " // message to confirm removal from queue
#define REMOVE_FAIL_QUEUE_IS_EMPTY "Currently the queue is empty. Got %d instead " // message for failed removal from the queue
#define CURRENT_QUEUE_STATE "Currently the queue is: " // message present queue state

/* ==================================== Main program section ====================================== */
/* This program creates a simple queue by using an array with a given size and has initialize function where setting the default value for all elements in the queue.
 * There is an input function that inserts an int at the end of the queue and an output function that returns the first insert item and shifts all elements.
 * There is an simple testing script that runs 2 for loops in main that tests the functionality and displays the results. There is a simple method printing the queue.*/

// Define functions
void initQue (int list [], int max ); // initialize queue
int input (int list [] , int number, int max); // insert in the queue a given number
int output( int list[], int max); // return the first element in the queue and shift the rest
void printQue(int list[]); // for testing prints the queue

int main() {
    // Variable declarations
    int items[MAX_SIZE_QUEUE]; // store the queue elements
    int removedNumber; // for testing used to store removed number
    initQue(items, MAX_SIZE_QUEUE); // call function to initialize the queue
    printQue(items); // display queue
    // Insert 6 numbers in the queue while printing the status and the updated que every time
    for (int i = 1; i <= 6; i++) {
        if (input(items, i, MAX_SIZE_QUEUE)){ // call function to insert item, that returns 1 on successes
            printf(INSERT_SUCCESSFUL, i); // print success message
            printQue(items); // call function to print queue
        } else {
            printf(INSERT_FAIL_QUEUE_IS_FULL, i); // print fail message
            printQue(items); // call function to print queue
        }
    }
    // Remove 6 numbers from the queue while printing the status and the updated que every time
    for (int i = 1; i <= 6; i++) {
        removedNumber = output(items, MAX_SIZE_QUEUE); // remove the first number from the queue, if the return is 0 the queue is empty
        if (removedNumber == 0) {
            printf(REMOVE_FAIL_QUEUE_IS_EMPTY, removedNumber); // print fail message
        } else {
            printf(REMOVE_ITEM_SUCCESSFUL, removedNumber); // print success message
            printQue(items); // call function to print queue
        }
    }
    return 0; // Exit the program
}

//----------Functions Section------------

// Function for testing used to print the queue
void printQue(int *list) {
    printf(CURRENT_QUEUE_STATE); // display starting to print
    for(int i = 0; i < MAX_SIZE_QUEUE; i++) {
        printf("%d ", list[i]); // iterate over the queue and print every number
    }
    printf("\n"); // finish with new line
}
// Function for initializing the queue with default values
void initQue(int *list, int max) {
    for (int i = 0; i < max; i++) { // iterate over the size of the que
        *list = INITIAL_ITEM_VALUE;  // set every item to initial value
        list++; // increment the pointer
    }
}
// Function used to insert a number at the end of the queue
int input(int *list, int number, int max) {
    if (list[max-1] != INITIAL_ITEM_VALUE) { // if the last value in the queue is not empty(initial value) the que is full
        return FALSE; // return 0 for full queue
    }
    while (*list) { // iterate over the array pointers
        if (*list == INITIAL_ITEM_VALUE) { // if a position is free
            *list = number; // add the number there
            return TRUE; // confirm
        }
        list++; // increment the pointer
    }
    return FALSE; // if there are no free spaces return 0
}
// Function used to remove an item from the start of the queue
int output(int *list, int max) {
    int i = 0; // use for index
    if (*list == INITIAL_ITEM_VALUE) { // if the first item is empty the queue is empty
        return 0; // return 0 when queue is emtpy
    }
    int firstNumber = *list; // save the first value from the queue
    for (i = 0; i < max-1; i++) { // iterate over the queue
        list[i] = list[i+1];  // shift all elements by one
    }
    list[max-1] = INITIAL_ITEM_VALUE; // set the last element in the queue to default value to avoid memory inconsistency
    return firstNumber; // return the first element in the array
}
