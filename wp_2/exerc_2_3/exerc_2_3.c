/* ====================================
File name: exerc_2_3.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

// Define section
#define NO_ARGUMENTS_MESSAGE "You didn't provide any arguments....\n" // used as error message when there are no strings
#define TO_FEW_ARGUMENTS_MESSAGE "You need to provide 2 strings....\n" // used as error message when there are less than 2 strings
#define TO_MANY_ARGUMENTS_MESSAGE "Please provide only 2 strings for comparison....\n" // used as error message when there are more than 2 strings
#define STRINGS_ARE_NOT_EQUAL_MESSAGE "The given strings: %s and %s are NOT equal\n" // used to notify when 2 given strings are not equal
#define STRINGS_ARE_EQUAL_MESSAGE "The given strings: %s and %s are equal\n" // used to notify when 2 given strings are equal
#define LIBRARY_COMPARISON_MESSAGE "The strings are compared with library function strcmp\n\tResult: " // Used to show that the library comparison is to run
#define CUSTOM_COMPARISON_MESSAGE "The strings are compared with custom function\n\tResult: " // Used to show that the custom comparison is to run
#define FALSE 0 // define boolean false
#define TRUE 1 // define boolean true

/* ==================================== Main program section ====================================== */
/* This program takes 2 arguments(strings) as command line parameters and compares them using a library method strcmp and a custom function.
 * After comparison the equality result is printed in command line.*/

// Function declaration
int compareStrings(char *firstString, char *secondString); // compares strings using library function
int compareStringsCustom(char *firstString, char *secondString); // compares using custom loop
void printEquality(int stringAreEqual, char *firstString, char *secondString); // displays the result
void handleInvalidArg(int argc); // used to handle errors from arguments provided

int main(int argc, char *argv[]) {
    // Variable declarations
    int stringAreEqual = FALSE; // define and assign boolean variable for equality
    if (argc != 3){ // Handle not valid number of arguments
        handleInvalidArg(argc); // call function to handle error
    }

    printf(LIBRARY_COMPARISON_MESSAGE); // display that the comparison library function is run
    stringAreEqual = compareStrings(argv[1], argv[2]); // call function to compare string parameters from arguments given by using strcmp
    printEquality(stringAreEqual, argv[1], argv[2]); // call function to display the result

    printf(CUSTOM_COMPARISON_MESSAGE); // display that the custom comparison function is run
    stringAreEqual = compareStringsCustom(argv[1], argv[2]); // call function to compare string parameters from arguments given by using custom loop
    printEquality(stringAreEqual, argv[1], argv[2]); // call function to display the result

    return 0; // Exit the program
}

//----------Functions Section------------

// Function used to handle error conditions from arguments
void handleInvalidArg(int argc) {
    if(argc == 1) { // Handle no parameters given
        printf(NO_ARGUMENTS_MESSAGE); // display message for no strings provided
        exit(0);  // exit program with 0 expected behavior
    } else if ( argc > 3) { // Handle more than 2 strings provided
        printf(TO_MANY_ARGUMENTS_MESSAGE); // display message for more than 2 strings
        exit(0); // exit program with 0 expected behavior
    } else if (argc == 2){ // Handle only one string
        printf(TO_FEW_ARGUMENTS_MESSAGE); // display message for less than 2 strings
        exit(0); // exit program with 0 expected behavior
    }
}
// Function used to print if the 2 strings are equal or not based on the previous comparison
void printEquality(int stringAreEqual, char *firstString, char *secondString) {
    if (stringAreEqual) {
        printf(STRINGS_ARE_EQUAL_MESSAGE,firstString, secondString); // Display equal message with the strings
    } else {
        printf(STRINGS_ARE_NOT_EQUAL_MESSAGE,firstString, secondString); // Display not equal message with the strings
    }
}
// Function to compare 2 strings(array of char) using a loop
int compareStringsCustom(char *firstString, char *secondString) {
    while (*firstString !='\0' || *secondString != '\0') { // loop while end of strings is not found
        if(*firstString != *secondString) { // compare the chars where the pointers are pointing too
            return FALSE; // strings are not equal
        }
        firstString++; // increment pointer
        secondString++; // increment pointer
    }
    return TRUE; // strings are equal
}
// Function to compare 2 strings(array of char) using strcmp library function
int compareStrings(char *firstString, char *secondString) {
    if (strcmp(firstString, secondString) != 0) { // Call strcmp to compare strings and check if they are not equal
        return FALSE; // if not equal return false
    } else {
        return TRUE; // executed if strings are equal
    }
}
