/* ====================================
File name: decode.c (or cpp)
Date: 2021-02-18
Group nr 14IIm
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 8336
====================================== */

// Include section
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

#define TRUE 1 // Define true
#define FALSE 0 // Define false
#define ALLOWED_CHARS "0123456789abcdefABCDEF" // Characters used to check for allowed hexadecimal characters
#define ENGINE_ON "engine_on: %d \n" // String to print value for engine on
#define GEAR_POS "gear_pos: %d \n" // String to print value for gear position
#define KEY_POS "key_pos: %d \n" // String to print value for key position
#define BRAKE1 "brake1: %d \n" // String to print value for brake 1
#define BRAKE2 "brake2: %d \n" // String to print value for brake 2
#define INVALID_HEX "You've provided an invalid hexadecimal number\n" // Error string when an invalid hex is given

/* This program gets an hexadecimal as an argument from the user, validates the hexadecimal and splits the bits to
 * corresponding values in a table to be printed for the different values for the car.
 */


int validateArgs(int argc, char *argv[]); // Define method to be used to validate arguments given by user
unsigned int getBits(unsigned int dec_val, int startPos, int numOfBits); // Define method that gets the bit values from the digit value of a hexadecimal


int main(int argc, char *argv[]){
    // Declare variables
    unsigned int hexValue;  // Digit value for the hexadecimal
    unsigned int engine_on; // Save the bit value for engine on
    unsigned int gear_pos; // Save the bit value for gear position
    unsigned int key_pos; // Save the bit value for key position
    unsigned int brake1; // Save the bit value for brake 1
    unsigned int brake2;   // Save the bit value for brake 2

    if(validateArgs(argc, argv)){ //if statement to check that a valid argument was given
        hexValue  = (unsigned int) strtol(argv[1], NULL, 16); //Turn the hexadecimal to it's digit value
        engine_on = getBits(hexValue, 7, 1); // Get the bit used for engine on from the hexvalue
        gear_pos = getBits(hexValue, 4, 3); // Get the bit used for gear position from the hexvalue
        key_pos = getBits(hexValue, 2, 2); // Get the bit used for key position from the hexvalue
        brake1 = getBits(hexValue, 1, 1); // Get the bit used for brake 1 from the hexvalue
        brake2 = getBits(hexValue, 0 , 1); // Get the bit used for brake 2 from the hexvalue
        printf(ENGINE_ON, engine_on); // Print the bit value for engine on
        printf(GEAR_POS, gear_pos); // Print the bit value for gear position
        printf(KEY_POS, key_pos); // Print the bit value for key position
        printf(BRAKE1, brake1); // Print the bit value for brake 1
        printf(BRAKE2, brake2); // Print the bit value for brake 2
    }else {
        printf(INVALID_HEX); //On invalid argument given, print error string
    }
    return 0; // Exit the program
}

// Method to validate the arguments to be a proper hexadecimal given from the user
int validateArgs(int argc, char *argv[]){
    if(argc == 2){ // Check that only one argument is given
        if(strlen(argv[1]) > 0 && strlen(argv[1]) < 3) { // Check that the given hexadecimal is max length of 2
            if (argv[1][strspn(argv[1], ALLOWED_CHARS)] == 0) { // Validate that the hexadecimal fits to the allowed characters
                return TRUE; // Return true for a valid hexadecimal
            }
        }
    }
    return FALSE; // Return false for invalid hexadecimal
}

//MEthod to get the bit value from a hexadecimal value
unsigned int getBits(unsigned int value, int startPos, int numOfBits) {
    unsigned int bitValue; // int to save the bitvalue into
    unsigned mask; // Mask used for AND statement to get the bit values that you want
    mask = ((1 << numOfBits) - 1) << startPos; // shift the bits to save only the amount of bits wanted from the start position
    bitValue = value & mask; // AND statement to save the bits wanted into bitvalue
    bitValue = bitValue >> startPos; // Shift the bitvalue to startpos to get all the bits to the right
    if ((startPos == 4 && bitValue > 4) || (numOfBits == 1 && bitValue > 1) || (startPos == 2 && bitValue > 2)) { // Check that the hex given doesn't give an out of bounds value for what we need
        printf(INVALID_HEX); // Print error string
        exit(0); // Exit the program on invalid hex
    }
    return bitValue; // Return the bitvalue that was asked for
}