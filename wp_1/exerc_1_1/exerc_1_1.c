/* ====================================
File name: exerc_1_1.c (or cpp)
Date: 2020-01-26
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: [<Ass code 1-4> <abc>]
====================================== */

// Include section
#include "stdio.h"
#include "string.h"

// Define section
#define INPUT_PROMP "Please enter a number between 1 and 5.\n" // Prompt user for a number
#define SENTENCE_ONE   "You selected 1 \n" // Sentence to be printed for option 1
#define SENTENCE_TWO   "You selected 2 \n" // Sentence to be printed for option 2
#define SENTENCE_THREE "You selected 3 \n" // Sentence to be printed for option 3
#define SENTENCE_FOUR  "You selected 4 \n" // Sentence to be printed for option 4
#define SENTENCE_FIVE  "You selected 5 \n" // Sentence to be printed for option 5
#define SENTENCE_WRONG_INPUT "Not a valid input \n" // Invalid input prompt
#define MAX_SIZE 8 // Bytes allocated to input characters
#define LOWER_INVALID_INPUT 0 // Lower integer threshold for an invalid input
#define UPPER_INVALID_INPUT 6 // Upper integer threshold for an invalid input

/* ==================================== Main program section ====================================== */
/* This program prints out one of five sentences based on the input given by the user (1-5), given an invalid input,
 * the program exits. The program continues to run as long as valid inputs are given. */

// Function to print a sentence based on a valid input integer
void displaySentence(int selectedOption) {
    switch (selectedOption) { // Switch statement handles input integer from the user
        case 1:
            printf(SENTENCE_ONE); // Prints sentence 1 and then breaks from the switch
            break;
        case 2:
            printf(SENTENCE_TWO); // Prints sentence 2 and then breaks from the switch
            break;
        case 3:
            printf(SENTENCE_THREE); // Prints sentence 3 and then breaks from the switch
            break;
        case 4:
            printf(SENTENCE_FOUR); // Prints sentence 4 and then breaks from the switch
            break;
        case 5:
            printf(SENTENCE_FIVE); // Prints sentence 5 and then breaks from the switch
            break;
        default:
            printf(SENTENCE_WRONG_INPUT); // Default case handles invalid integer input and then breaks from the switch
            break;
    }
}

int main() {
    // Variable declarations
    char input[MAX_SIZE]; // Character array to store user input
    int selectedOption; // Extracted integer from character array

    // Main loop to prompt user for input at least once
    do {
        printf(INPUT_PROMP); // Ask user to enter an integer value
        fgets(input, sizeof (input), stdin); // Read input buffed and store it into character array

        if (sscanf(input, "%d", &selectedOption) != 1 || strlen(input) != 2) {   // Read integers from the stored character array
                                                                                        // Check if the input doesn't contain an integer value
                                                                                        // Check if the stored character array is not of size 2 (including \n)
            printf(SENTENCE_WRONG_INPUT);                                               // If any of the  conditions are true, we notify the user
            return 0;                                                                   // and exit the program
        }

        displaySentence(selectedOption); // Run function to display sentence based on user input
    } while (selectedOption > LOWER_INVALID_INPUT && selectedOption < UPPER_INVALID_INPUT); // Run the loop while selectedOption is within the allowed bounds

    return 0; // Exit the program
}