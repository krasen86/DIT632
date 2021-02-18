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
/* This program gets 5 integer values as input parameters when running it, one that defines engine_on
 * (0,1), a second for gear_pos (0-4), a third for key_pos (0-2), a fourth for brake1 (0,1) and the
 * fifth for brake2 (0,1). After validating the input the program returns to the user the corresponding
 * hexadecimal value of the binary representation of the input. For example, when 1 2 2 1 1 has been
 * entered, with a binary representation of 10101011, then the hexadecimal value of AB shall be returned
 * to the user.
 * */

// Function declaration
int validateInputArguments(int size, char *arguments[]);
unsigned char setParameters(int size, char *arguments[]);

int main(int argc, char *argv[]) {
    // Variable declarations
    int validArguments = FALSE; // define boolean flag for verifying provided arguments
    unsigned char parameters; // used to store the parameters as unsigned char

    if (argc == 6) { // check if the number of arguments is a valid one, i.e. 5 plus one for the execution of the program
        validArguments = validateInputArguments(argc, argv); // call a function to check if the parameters are within a valid bounds and assign the returned value to validArguments variable
        if (validArguments) { // case of the arguments being within the valid corresponding bounds
            parameters = setParameters(argc, argv); // call the setParameters function that
            printf("%X \n",parameters); // print the parameters' hexadecimal representation
        }
    } else { // handle invalid number of provided arguments
        printf(INVALID_NUMBER_ARGUMENTS); // print error message to the user
        return 0; // exit the program in case of error
    }
    return 0; // Exit the program
}

// Function to translate the decimal values of the input parameters to binary.
unsigned char setParameters(int size, char *arguments[]) {
    unsigned char parameters; // store the parameters
    /* the following code block converts the decimal values of the arguments
     * to a binary representation of it, by first applying bit shifting to
     * the value an X number of places until it gets to the correct position.
     * Then, by applying the logical OR operation among all the "translations",
     * we get the final representation of the input parameters in binary.
    */
    parameters = (*arguments[5] - '0'); // store the last parameter's value in binary
    parameters |= (*arguments[1] - '0') << 7; // apply bit shifting to the binary value of the first argument, then apply logical OR operation to the previous value of the parameters and store its value
    parameters |= (*arguments[2] - '0') << 4; // apply bit shifting to the binary value of the second argument, then apply logical OR operation to the previous value of the parameters and store its value
    parameters |= (*arguments[3] - '0') << 2; // apply bit shifting to the binary value of the third argument, then apply logical OR operation to the previous value of the parameters and store its value
    parameters |= (*arguments[4] - '0') << 1; // apply bit shifting to the binary value of the fourth argument, then apply logical OR operation to the previous value of the parameters and store its value

    return parameters; // return the parameters
}

// Function to validate the input arguments
int validateInputArguments(int size, char *arguments[]) {
    int i = 1; // define index for loop starts from 1 in order to not count function name
    int parsedArgument; // integer representation of the argument char

    // loop to iterate through the argument's values
    for(i; i < size; i++) {
        if (arguments[i][0] == '-') { // exclude negative values
            return FALSE;
        }
        if (isdigit(*arguments[i])) { // check if the argument is digit
            parsedArgument = (*arguments[i] - '0'); // store the argument's value to an integer variable
            if (i == 2) { // case of 'gear_pos' argument
                if (parsedArgument > 4) { // check if invalid input has been entered for gear_pos, i.e. greater than 4
                    return FALSE; // return false to the function's call
                }
            } else if (i == 3) { // case of 'key_pos' argument
                if (parsedArgument > 2) { // check if invalid input has been entered for key_pos, i.e. greater than 2
                    return FALSE; // return false to the function's call
                }
            } else { // every other argument that takes values of 0 and 1 as valid ones
                if (parsedArgument > 1) {  // check if its value is out of bounds
                    return FALSE; // return false to the function's call
                }
            }
        } else { // the argument was not a digit
            return FALSE; // return false to the function's call
        }
    }
    return TRUE; // the input was valid, thus return true to the function's call
}