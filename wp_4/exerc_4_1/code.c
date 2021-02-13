/* ====================================
File name: code.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14IIm
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <ctype.h>
#include "stdio.h"

// Define section
#define INVALID_NUMBER_ARGUMENTS "Please provide 5 values to set the parameters.\n" // used to notify the user for invalid amount of arguments
#define FALSE 0; // define boolean false
#define TRUE 1; // define boolean true

/* ==================================== Main program section ====================================== */
/* This program TODO..... */

// Function declaration
int validateInputArguments(int size, char *arguments[]);
unsigned char setParameters(int size, char *arguments[]);

int main(int argc, char *argv[]) {
    // Variable declarations
    int validArguments = FALSE; // define boolean flag for verifying provided arguments
    unsigned char parameters;

    if (argc == 6) {
        validArguments = validateInputArguments(argc, argv); // call a function to check if the parameters are within a valid bounds
        if (validArguments) {
            parameters = setParameters(argc, argv);
            printf("%X \n",parameters);
        }
    } else { // handle invalid number of provided arguments
        printf(INVALID_NUMBER_ARGUMENTS);
        return 0;
    }
    return 0; // Exit the program
}
unsigned char setParameters(int size, char *arguments[]) {
    unsigned char parameters;
    parameters = (*arguments[5] - '0');
    parameters |= (*arguments[1] - '0') << 7;
    parameters |= (*arguments[2] - '0') << 4;
    parameters |= (*arguments[3] - '0') << 2;
    parameters |= (*arguments[4] - '0') << 1;
    return parameters;
}

int validateInputArguments(int size, char *arguments[]) {
    int i = 1; // define index for loop starts from 1 in order to not count function name
    int parsedArgument; // integer representation of the argument char

    for(i; i < size; i++) {
        if (arguments[i][0] == '-') {
            return FALSE;
        }
        if (isdigit(*arguments[i])) {
            parsedArgument = (*arguments[i] - '0');
            if (i == 2) {
                if (parsedArgument > 4) {
                    return FALSE;
                }
            } else if (i == 3) {
                if (parsedArgument > 2) {
                    return FALSE;
                }
            } else {
                if (parsedArgument > 1) {
                    return FALSE;
                }
            }
        } else {
            return FALSE;
        }
    }
    return TRUE;
}