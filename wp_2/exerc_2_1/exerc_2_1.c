/* ====================================
File name: exerc_2_1.c (or cpp)
Date: 2021-02-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: 5202
====================================== */

// Include section
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
// Define section
#define MAX_STRING_LENGTH 20 // maximum size of string
#define PROMP_USER_FOR_STRING_INPUT "Please enter a string of maximum 20 characters...\n"// string to ask the user to enter input TODO check for different solution
#define RESULT_STRING_USING_STRCPY "String: <%s> copied result using strcpy: <%s> \n" // output result to user for coping using strcpy
#define RESULT_STRING_USING_CUSTOM "String: <%s> copied result using custom function: <%s> \n" // output result to user for coping using custom function
#define EMPTY_STRING_MESSAGE "There is nothing to be copied...\n" // string for handling empty file/input
#define END_OF_STRING '\0' // define end of string
/* ==================================== Main program section ====================================== */
/* This program reads a string of maximum of 20 characters and creates a copy of that string using a custom method (loop) and a library method.
 * The result of both copies is printed to the screen. Optionally the user may use a file instead of inputting the sting manually. */

//Function declaration
void copyString(char *initialString, char *copiedString); // Used to copy strings from one pointer to another
void copyStringCustom(const char *initialString, char *copiedString); // Used to copy strings from one pointer to another whit loop
void exitProgramme(); // function to exit programme
void freeMemoryChar (char *pointer); // used to free memory of a given pointer

int main() {
    // Variable declarations
    char initialString[MAX_STRING_LENGTH]; // stores read string in array
    char *copiedString; // store copied string
    unsigned int initialStringLength = 0; // used to store the length of the string
    printf(PROMP_USER_FOR_STRING_INPUT); // promp user for input
    fgets(initialString, MAX_STRING_LENGTH + 1, stdin); // Read input from buffer whit new line taken into account and saving only the first 20 characters
    initialStringLength = strlen(initialString); // get and assign the length of the read string
    if (initialStringLength == 0 || initialString[0] == '\n') { // Check if the file is empty
        exitProgramme(); // Exit the program
    }
    if (initialString[initialStringLength - 1] == '\n') { // for strings less than 20 char check if new line is present
        initialString[initialStringLength - 1] = END_OF_STRING ; // replace new line with string end
    }
    copiedString = calloc(initialStringLength, sizeof(char)); // allocate memory for copy string
    copyString(initialString, copiedString); // Call method to copy string using strcpy
    printf(RESULT_STRING_USING_STRCPY, initialString, copiedString); // Print result
    freeMemoryChar(copiedString); // call function to free memory in order to use the same pointer to copy the sting again
    copiedString = calloc(initialStringLength, sizeof(char)); // allocate memory for copy string
    copyStringCustom(initialString, copiedString); // copy string with loop
    printf(RESULT_STRING_USING_CUSTOM, initialString, copiedString); // Print result
    freeMemoryChar(copiedString); // call function to free memory
    return 0; // Exit the program
}

// --------------Function section---------------

// The function copies the string by using the standard library function strcpy and pointers to the strings
void copyString(char *initialString, char *copiedString) {
    strcpy(copiedString, initialString); // call standard library function to copy the strings from the pointer to the array
}
// The function copies the string by using a loop
void copyStringCustom(const char *initialString, char *copiedString) {
    int i; // index used to iterate the array
    unsigned int lengthOfString = strlen(initialString);
    for (i = 0; i < lengthOfString; i++) {// iterate until end of the string char-array is reached
        copiedString[i] = initialString[i]; // copy elements in array
    }
    copiedString[lengthOfString] = END_OF_STRING; // set final string char to 0
}
// The function is used to handle exit programme when empty string or file is present, returns 0 since it's expected behavior
void exitProgramme() {
    printf(EMPTY_STRING_MESSAGE); // Print error message and processed to exit
    exit(0); // Exit programme
}
// Function used to free memory for char pointer
void freeMemoryChar (char* pointer) {
    free(pointer); // Free memory
    pointer = NULL; // Nullify the pointer
}