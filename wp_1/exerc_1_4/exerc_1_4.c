#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include "string.h"

#define MAX_NUMBER 5
#define INITIAL_PROMPT "Guess a number between 1-100\n"
#define GUESS_LOW "Guess is too low, number of tries: %d\n"
#define GUESS_HIGH "Guess is too high, number of tries: %d\n"
#define CORRECT_GUESS "You guessed correct! Total number of tries was %d \n"
#define FAIL_GUESS "Sorry you ran out of tries!\n"
#define PLAY_AGAIN "Would you like to play again? (y/n)?\n"
#define MAX_CHARACTERS 32

int getIntegerInput() {   
    char input[MAX_CHARACTERS];
    int userInput;
    fgets(input, sizeof (input), stdin);
    sscanf(input, "%d", &userInput);
    return userInput;
}

// TODO: Don't forget to validate the input data to accept only 1-100 values and do not regard it as a valid try otherwise.

int main() {
    char answer[MAX_CHARACTERS], answerChar;
    int guessedNumber, numberGuessed, numberOfTries, randomNumber;
    srand(time(NULL));

    do {
        numberGuessed = 0;
        randomNumber = rand() % 100 + 1;
        numberOfTries = 1;

        printf("%d\n", randomNumber);
        printf(INITIAL_PROMPT);
        do {
            guessedNumber = getIntegerInput();
            if (guessedNumber<randomNumber) {
                printf(GUESS_LOW, numberOfTries);
            }else if (guessedNumber>randomNumber) {
                printf(GUESS_HIGH, numberOfTries);
            }else {
                printf(CORRECT_GUESS, numberOfTries);
                numberGuessed = 1;
            }
            numberOfTries++;
        } while (guessedNumber != randomNumber && numberOfTries <= MAX_NUMBER);

        if (!numberGuessed) {
            printf(FAIL_GUESS);
        }

        printf(PLAY_AGAIN);
        fgets(answer, sizeof (answer), stdin);
        sscanf(answer, "%c", &answerChar);

        if (answerChar != 'y' || strlen(answer) > 2) {
            return 0;
        }

    } while (!feof(stdin));
}

