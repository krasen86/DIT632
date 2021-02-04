/* ====================================
File name: exerc_2_2.c (or cpp)
Date: 2021-02-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: 5202
====================================== */

// Include section
#include "stdio.h"
#include <time.h>
#include "stdlib.h"

// Define section
#define STRING_ARRAY_LABEL_ADDRESS "The value of the label array (address) is: %p\n" // String used for pointer address of array
#define STRING_ARRAY_FIRST_INTEGER "First integer in the array is (array[0]) : %d\n" // String used for first element in the array
#define STRING_INTEGER_SIZE_OF_BYTES "The size of an integer (number of bytes) is : %lu\n" // Printing size of array in bytes
#define STRING_ARRAY_SIZE "The size of the whole array is : %d (length) and %d (bytes) \n" // Print the length and byte size of the array
#define STRING_INTEGER_FORMAT "Integer value at position %d is %d\n" // Print the integer in int format and the coresponding position in the array
#define STRING_DOUBLE_FORMAT "Double value at position %d is %.2lf\n" // Print the integer in double format and the coresponding position in the array
#define ARRAY_MAX_LENGTH 10 // Used to set the size of the array

/* ==================================== Main program section ====================================== */
/* This program creates an array of integers, defined by ARRAY_MAX_LENGTH, and then fill it with random integers from 1 to 99.
 * Then the program prints out a short summary and all the numbers in the array in int and double format. */

// Define functions
void printSummary(int const numbersArray[]); // prints basic summary
void populateArrayWithRandomNumbers(int numbersArray[]); // populates the array with random numbers
void printArray(int const numbersArray[]); // Prints array in both int and double format
unsigned int getSizeBytes(int const numbersArray[]); // calculates the byte size given an int array pointer



int main() {
    // Variable declarations
    int numbersArray[ARRAY_MAX_LENGTH]; // Used to store the numbers
    populateArrayWithRandomNumbers(numbersArray);
    printSummary(numbersArray); // Call function to print the information about the array
    printArray(numbersArray);   // Call function to display the elements in the array
    return 0; // Exit the program
}

// --------------Function section---------------

// Function used to print the information about the array stored given a pointer
void printSummary(int const numbersArray[]) {
    printf(STRING_ARRAY_LABEL_ADDRESS, &numbersArray); // Prints the memory address
    printf(STRING_ARRAY_FIRST_INTEGER, *numbersArray); // Prints the first integer in the array
    printf(STRING_INTEGER_SIZE_OF_BYTES, sizeof(*numbersArray)); // Prints the size of the first integer in bytes
    printf(STRING_ARRAY_SIZE,ARRAY_MAX_LENGTH, getSizeBytes(numbersArray)); // Prints and calls function to calculate the byte size of the array since arrays are passed as pointers'
}
// Function used to get the byte size of a given pointer array
unsigned int getSizeBytes(int const numbersArray[]) {
    unsigned int sizeBytes = 0; // total bytes
    for (int i = 0; i < ARRAY_MAX_LENGTH; i++) { // iterate in the array
        sizeBytes = sizeBytes + sizeof(*numbersArray); // increment the total with each element size
        numbersArray++; // move pointer to next element
    }
    return sizeBytes; // return total
}
// Function used to populate the array with random numbers
void populateArrayWithRandomNumbers(int numbersArray[]) {
    srand(time(0)); // Generate seed for the creation of random numbers based on time function
    for (int i = 0; i < ARRAY_MAX_LENGTH; i++) { // iterate in the array
        *numbersArray = rand() % 99 + 1; // generate a new "random" number by using the rand() function, numbers is between 1-99
        numbersArray++; // increment to next pointer in the array
    }
}
// Function used to print the elements in the array in both int and double format
void printArray(int const numbersArray[]) {
    for (int i = 0; i < ARRAY_MAX_LENGTH; i++) { // iterate in the array
        printf(STRING_INTEGER_FORMAT, i, *numbersArray); // print integer in int format
        printf(STRING_DOUBLE_FORMAT, i , (double) *numbersArray); // print integer in double format
        numbersArray++; // increment pointer
    }
}