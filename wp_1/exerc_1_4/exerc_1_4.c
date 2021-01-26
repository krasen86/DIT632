/* ====================================
File name: exerc_1_4.c (or cpp)
Date: 2020-01-26
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: [<Ass code 1-4> <abc>]
====================================== */

// Include section
#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include "string.h"

// Define section
#define MAX_NUMBER_OF_GUESSES 5 // Maximum number of guesses in order to guess the correct one
#define INITIAL_PROMPT "Guess a number between 1-100\n" // String asking the user to enter a number
#define INVALID_INPUT_PROMPT "You entered an invalid number, number should be between 1-100. Try again! %d/%d tries left.\n" // String for printing an error message based on user's input
#define GUESS_LOW "Guess is too low, number of tries: %d out of %d\n" // String to be printed when the user guessed number is lower that the generated one
#define GUESS_HIGH "Guess is too high, number of tries: %d out of %d\n" // String to be printed when the user guessed number is higher that the generated one
#define CORRECT_GUESS "You guessed correct! Total number of tries was %d \n" // String to be printed when the user guessed the number
#define FAIL_GUESS "Sorry you run out of tries!\n" // String to be printed when the number of guesses has been exceeded
#define PLAY_AGAIN "Would you like to play again? (y/n)?\n" // String to ask the user if they would like to play another round of the game
#define MAX_CHARACTERS 32 // Maximum allowed characters for user input
#define LOWER_THRESHOLD_INVALID_INPUT 0 // Lower integer threshold for an invalid input
#define UPPER_THRESHOLD_INVALID_INPUT  101 // Upper integer threshold for an invalid input
#define EXIT_MESSAGE "Thank you for playing! Bye!\n" // String to be printed when program is terminated
#define MAX_NUMBER_OF_ERRORS 3 // Maximum number of allowed attempts (user input) until exiting the program
#define PROGRAM_TERMINATION_MESSAGE "Maximum number of tries exceeded. Exiting...\n"
#define FALSE 0 // Define false
#define TRUE 1 // Define true
#define PLAY_AGAIN_CONFIRMATION 'y' // Accepted positive answer representing yes

/* ==================================== Main program section ====================================== */
/* Simple number guessing name that a number is generated and the user tries to guess it within an X
 * amount of tries. Then a message is printed depending on if the number was lower/higher or correctly
 * guessed. If the user runs out of tries or guesses correctly, the user will be prompted to play
 * again or exit. */

// Function to read the buffer and validate if it's an integer value within the set bounds
int getIntegerInput() {
    // Variable declarations
    char input[MAX_CHARACTERS]; // Store user input into character array
    int userInput; // Extracted integer from character array
    int numberOfTries = 0; // Declare value index to keep track of the number of tries
    // Loop to ensure that only valid integer gets accepted
    do {
        fgets(input, sizeof (input), stdin); // Read input buffed and store it into character array
        sscanf(input, "%d", &userInput); // Read integers from the stored character array
        if (userInput > LOWER_THRESHOLD_INVALID_INPUT && userInput < UPPER_THRESHOLD_INVALID_INPUT) {   // Check if the userInput is within the allowed bounds
            return userInput;                                                                           // Return the userInput to the function that called it
        } else if (feof(stdin)) {                                                                       // Case where EOF has been entered by the user
            printf(EXIT_MESSAGE);                                                                       // Print exit message
            exit(0);                                                                             // terminate the program with success code, since it's an expected behaviour based on wrong user input
        } else {                                                                                        // userInput was invalid
            numberOfTries++;                                                                            // Increment number of available tries
            printf(INVALID_INPUT_PROMPT, MAX_NUMBER_OF_ERRORS - numberOfTries, MAX_NUMBER_OF_ERRORS);   // Print the number of remaining tries
        }

    } while (numberOfTries < MAX_NUMBER_OF_ERRORS);  // Run the loop until max number of allowed tries is reached

    // case that no valid user input received and max number of tries exceeded
    printf(PROGRAM_TERMINATION_MESSAGE); // print exit message
    exit(0); // terminate the program with success code, since it's an expected behaviour based on wrong user input
}

// Function to compare the guessed number and the generated one and print message corresponding
// to the difference between those numbers as well as printing the number of tries
int compareNumbers (int randomNumber,int guessedNumber, int numberOfTries) {
    int numberGuessed = FALSE; // variable to keep track whether the number was guessed correctly

    if (guessedNumber<randomNumber) {                               // Check if the guessed number is lower than the generated one
        printf(GUESS_LOW, numberOfTries, MAX_NUMBER_OF_GUESSES);    // print the appropriate message along with the number of tries
    }else if (guessedNumber>randomNumber) {                         // Check if the guessed number is higher than the generated one
        printf(GUESS_HIGH, numberOfTries, MAX_NUMBER_OF_GUESSES);   // print the appropriate message along with the number of tries
    }else {                                                         // The number was correctly guessed
        printf(CORRECT_GUESS, numberOfTries);                       // print a success message
        numberGuessed = TRUE;                                       // change the flag to true since the number was guessed correctly
    }

    return numberGuessed; // return either true or false corresponding to whether the number was guessed correctly or not
}

int main() {
    // Variable declarations
    char answer[MAX_CHARACTERS]; // Character array to store user input
    char answerChar; // Extracted integer from character array
    int guessedNumber; // Variable to store the number that the user guesses
    int numberGuessed; // Boolean to decide whether the guessed number equals the generated one
    int numberOfTries; // Store the number of tries that have been processed
    int randomNumber; // Store the random number that has been generated

    srand(time(NULL)); // Generate seed for the creation of random numbers based on time function

    // Main loop to prompt user for a number and whether they want to play again or not
    do {
        numberGuessed = FALSE; // variable to keep track whether the number was guessed correctly
        randomNumber = rand() % 100 + 1; // generate a new "random" number by using the
        numberOfTries = 1; // set number of tries to 1 for the first iteration

        printf(INITIAL_PROMPT); // prompt the user to guess a number
        // Inner loop to iterate until max number of guesses or correctly guessed number
        do {
            guessedNumber = getIntegerInput(); // Call function to get validated user input
            numberGuessed = compareNumbers (randomNumber, guessedNumber, numberOfTries); // Assign value to the flag depending on the comparison outcome
                                                                                         // of the guessed number and the generated one
            numberOfTries++;  // increment the number of tries
        } while (!numberGuessed && numberOfTries <= MAX_NUMBER_OF_GUESSES); // iterate whenever the number was not guessed correctly
                                                                            // and the number of max tries has not been exceeded

        if (!numberGuessed) {    // If number was not guessed within X amount of tries
            printf(FAIL_GUESS);  // print a message to the user
        }
        printf(PLAY_AGAIN); // Prompt the user if they want to play again

        fgets(answer, sizeof (answer), stdin); // Read input buffed and store it into character array
        sscanf(answer, "%c", &answerChar); // Read character from the stored character array
        if (answerChar != PLAY_AGAIN_CONFIRMATION || strlen(answer) > 2 || feof(stdin)) { // Check if the user wants to play again
                                                                                          // if the length of the input is greater than 2 characters
                                                                                          // and if the EOF has been entered
            printf(EXIT_MESSAGE); // print exit message to the user
            return 0; // exit the program
        }

    } while (TRUE); // Main loop runs as an infinite loop (the program terminates based on user input)

    return 0; // Exit the program
}

