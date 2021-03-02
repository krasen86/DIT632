/* ====================================
File name: exerc_6_2.c
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define section
#define NUM_ELEMENTS 200 // maximum number of elements in array
#define THREAD_EXECUTION_ARRAY_FILLING "Executing \"filling the array\"...\n" // message printed when the thread for populating the array starts
#define THREAD_EXECUTION_ARRAY_SORTING "Executing \"sorting the array\"...\n" // message printed when the thread for sorting the array starts
#define THREAD_EXECUTION_ARRAY_SEARCHING "Executing \"searching for the number in the array\"...\n" // message printed when the thread for binary search of number in the array starts
#define READ_MAX_VALUE_MESSAGE "Enter max value:" // Prompt message to enter a max value for a random number
#define READ_NUMBER_MESSAGE "Enter value to find:" // Prompt message to enter a number that is to be found in the array
#define NUMBER_FOUND_MESSAGE "\n%d found at location %d.\n" // Notification printed when the number is found in the array, prints first the number and than the position in the array
#define NUMBER_NOT_FOUND_MESSAGE "\n Not found! %d is not present in the list.\n" // Notification for number not found

/* ==================================== Main program section ====================================== */
/* This program creates an array with random numbers based on a max value given by the user. The programme than sorts the array and asks the user to enter a number.
 * When the user enters a number the programme checks if the array contains the number and prints a confirmation, if the number is found, or a number not found notification.
 * The programme uses multiple threads to run the steps describe above ( a thread for populating the array, a thread for sorting the array, and a thread for finding if a number
 * is present in the array. The threads are executed one after another.*/

// Declaration section
int numbers[NUM_ELEMENTS]; // store the numbers in array
int maxValue; // stores max value for random number generation

//Function declaration
void *populateArray(void *param); // function to be executed on thread populating the array with numbers
void *sort(void *param); // function to be executed on thread sorting the numbers in the array
void *findNumber(void *number); // function to be executed on thread finding a given number in an array
int readNumber(); // function to read number from the user

//Main
int main() {
    // Variable declaration
    int number; // store number read from user
    time_t t; // time type used for the srand function for the rondom number
    pthread_t threadID; // pthread structure to store the created threads ids
    pthread_attr_t attr; // att_r structure to store the attributes for the initialization of the threads when created

    srand((unsigned) time(&t)); // Generate seed for the creation of random numbers based on time function
    pthread_attr_init(&attr); // initialize the attributes to default

    maxValue = readNumber(READ_MAX_VALUE_MESSAGE); // call function to read user input for max value

    pthread_create(&threadID, &attr, populateArray, NULL); // create thread assign the thread id to the pointer threadID, pass the default initialized attributes pointer, attach the function for populating the array to the thread and pass Null arguments to the function
    pthread_join(threadID, NULL); // wait for the created thread to finish, Null is provided since the thread function does not return anything

    pthread_create(&threadID, &attr, sort, NULL); // create a new thread and reuse the pointer threadID for the thread id, pass the default initialized attributes pointer, attach the function for sorting the array to the thread and pass Null arguments to the function
    pthread_join(threadID, NULL); // wait for the sorting thread to finish, Null is provided since the thread function does not return anything

    number = readNumber(READ_NUMBER_MESSAGE); // call function to read user input for the number to be found

    pthread_create(&threadID, &attr, findNumber,(void *) &number); // create a new thread and reuse the pointer threadID for the thread id, pass the default initialized attributes pointer, attach the function for finding a number in the array to the thread and pass the number as argument to the function
    pthread_join(threadID, NULL); // wait for the find number thread to finish execution, Null is provided since the thread function does not return anything

    return 0; // exit programme
}
// Function to read user integer input and return it
int readNumber(char *message) {
    // Variable declaration
    int number; // store the number read
    printf("%s\n", message); // display prompt message
    scanf("%d", &number); // read the numeric input with scanf until a space

    return number; // return the number
}
// Thread function used to populate the array with void pointers as parameters
void *populateArray(void *param) {
    // Variable declaration
    int i, j; // define loop indexes
    printf(THREAD_EXECUTION_ARRAY_FILLING); // print start or thread
    for (i = 0; i < NUM_ELEMENTS; i++) { // loop into the max number of elements
        for(j=0; j<1000; j++); // To delay a bit
        numbers[i] = rand() % maxValue; // initialize the position of the array with a random number between zero and maxValue
    }

    pthread_exit(0); // exit thread without returning anything
}
// Thread function used to sort the array using bubble sort
void *sort(void *param) {
    // Variable declaration
    int i, j, swap; // declare indexes for loop and a swap variable

    printf(THREAD_EXECUTION_ARRAY_SORTING); // print start of thread message
    for (i = 0; i < NUM_ELEMENTS; i++) { // start first loop of sorting
        for (j = 0; j < NUM_ELEMENTS - i - 1; j++) { // inner loop
            if (numbers[j] > numbers[j + 1]) { // compare the 2 adjacent numbers
                swap = numbers[j]; // if bigger assign to swap
                numbers[j] = numbers[j + 1]; // assign the lower one to the previous position
                numbers[j + 1] = swap; // assign the higher value from the swap to the higher position
            }
        }
    }
    pthread_exit(0);  // exit thread without returning anything
}
// Thread function used to find if a given number is present in the array using binary search
void *findNumber(void *numberPointer) {
    // Variable declaration
    int first = 0; // assign the first index to zero
    int last = NUM_ELEMENTS - 1; // assign the last index to last index of the array
    int middle = (first + last) / 2; // find the middle
    int *number = (int *) numberPointer; // create and assign the number argument from the void pointer to a int pointer
    printf(THREAD_EXECUTION_ARRAY_SEARCHING); // print start thread message
    int i; // loop index
    for(i=0; i<NUM_ELEMENTS; i++){ // loop in the array
        printf(" %d", numbers[i]); // print every number of the array
    }
    printf("\n"); // finish the printing of the array with a new line

    while (first <= last) { // start binary search loop while first index doesn't pass the last index
        if (numbers[middle] == *number) { // base case number is found
            printf(NUMBER_FOUND_MESSAGE, *number, middle + 1); // print number found message and the position
            break; // break the while loop
        } else if (numbers[middle] < *number) { // check if the number is higher than the middle element
            first = middle + 1; // update the first index to middle
        } else { // case if the number is smaller than the middle
            last = middle - 1; // update the last index
        }
        middle = (first + last) / 2; // number not found from the iteration so the middle needs to updated
    }
    if (first > last) { // if the indexes have been updated and first is higher than the last number is not found
        printf(NUMBER_NOT_FOUND_MESSAGE, *number); // print number not found message
    }

    pthread_exit(0);  // exit thread without returning anything
}