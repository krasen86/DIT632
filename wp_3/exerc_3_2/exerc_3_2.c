/* ====================================
File name: exerc_3_2.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include "stdio.h"

// Define section
#define NOT_FOUND -1 // use for when number is not present in array
#define NOT_FOUND_MESSAGE "Number not found in array\n" // used to notify when number is not present
#define FOUND_MESSAGE "Number found in array at position %d.\n" // used to confirm that the number is present and print the position

/* ==================================== Main program section ====================================== */
/* This program ..... */
/*
 * a)Write a function that given an integer n, an array of integers and the size of the array determines if n is in the array.
 * If so the function should return the index for the first position of the number (in case of several) otherwise returns  -1.
 * For testing the function, write a main program that tests the function with help of an array initiated in the main program as below and with a function declaration:
 * int search_number( int number, int tab[], int size);int test [] = { 1,2,34,5,67,3,23,12,13,10};
*/
// Function declaration
int search_number( int number, int tab[], int size);
int readNumber();

int main() {
    // Variable declarations
    int test [] = { 1,2,34,5,67,3,23,12,13,10};
    int number = readNumber();
    int position = search_number(number, test, sizeof(test)/sizeof(test[0]));
    if (position == NOT_FOUND) {
        printf(NOT_FOUND_MESSAGE);
    } else {
        printf(FOUND_MESSAGE, position);
    }
    return 0; // Exit the program
}

int readNumber() {
    return 0;
}

int search_number(int number, int tab[], int size){
    for (int i = 0; i < size; i++) {
        if (tab[i] == number) {
            return i;
        }
    }
    return NOT_FOUND;
}
