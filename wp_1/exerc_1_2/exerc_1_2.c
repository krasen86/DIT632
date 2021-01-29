/* ====================================
File name: exerc_1_2.c (or cpp)
Date: 2021-01-26
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 4783
====================================== */

// Include section
#include "stdio.h"
#include "string.h"

// Define section
#define INPUT_PROMP "Enter a sentence\n" // Prompt user for a sentence
#define WORD_COUNT_NOTIFICATION "Total number of words in the sentence is: %d\n" // Notify user amount of words in sentence
#define MAX_CHARACTERS 500 // Maximum allowed characters for user input
#define FALSE 0 // Define false
#define TRUE 1 // Define true

/* ==================================== Main program section ====================================== */
/* The program prompts the user for a sentence and then proceeds to count the amount of words
 * in the sentence and then prints the total to the user */

int main() {
    // Variable declarations
    char inputSentence[MAX_CHARACTERS]; // Store user input into character array
    int wordCount = 0; // Integer to count the amount of words in the sentence
    int i; // Integer for the for loop to iterate
    int foundLetter = FALSE; // Boolean value to check if a letter is found

    printf(INPUT_PROMP); // Prompt user for input
    fgets(inputSentence, MAX_CHARACTERS, stdin); // Read user input from buffer and store into character array

    // Main loop to iterate over the input characters stored in character array
    for (i = 0; i < strlen(inputSentence); i++) {
        if (inputSentence[i] == ' ' || inputSentence[i] == '\n') { // Check if a character is an empty space or a line break
            foundLetter = FALSE;                                   // If conditions are true, a letter is not found
        }     
        else { // Everything except space or line break is allowed
            if (!foundLetter) { // When a letter is found after an empty space or on the first iteration
                wordCount++;            // the word count will be incremented
            }   
            foundLetter = TRUE; // Boolean set to true because else statement found an allowed character,
                                // in order to prevent incrementing the wordCount for every character
        }
    }

    printf(WORD_COUNT_NOTIFICATION, wordCount); // Once the character array has been iterated through,
                                                // the program prints a sentence with the word count
    return 0; // Exit the program

}