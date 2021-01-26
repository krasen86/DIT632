/* ====================================
File name: exerc_1_4.c (or cpp)
Date: 2020-01-26
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: [<Ass code 1-4> <abc>]
====================================== */

#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include "string.h"

#define MAX_NUMBER 5
#define INITIAL_PROMPT "Guess a number between 1-100\n"
#define INVALID_INPUT_PROMPT "You entered an invalid number, number should be between 1-100. Try again!\n"
#define GUESS_LOW "Guess is too low, number of tries: %d out of %d\n"
#define GUESS_HIGH "Guess is too high, number of tries: %d out of %d\n"
#define CORRECT_GUESS "You guessed correct! Total number of tries was %d \n"
#define FAIL_GUESS "Sorry you ran out of tries!\n"
#define PLAY_AGAIN "Would you like to play again? (y/n)?\n"
#define MAX_CHARACTERS 32
#define VALID_INTEGER_INPUT 1

int getIntegerInput() {
    char input[MAX_CHARACTERS];
    int userInput;
    int validInput = 0;
    do {
        fgets(input, sizeof (input), stdin);
        sscanf(input, "%d", &userInput);
        if (userInput > 0 && userInput < 101) {
            validInput = VALID_INTEGER_INPUT;
        } else {
            printf(INVALID_INPUT_PROMPT);
        }

    } while (!validInput);

    return userInput;
}

int compareNumbers (int randomNumber,int guessedNumber, int numberOfTries) {
    int numberGuessed = 0;
    if (guessedNumber<randomNumber) {
        printf(GUESS_LOW, numberOfTries, MAX_NUMBER);
    }else if (guessedNumber>randomNumber) {
        printf(GUESS_HIGH, numberOfTries, MAX_NUMBER);
    }else {
        printf(CORRECT_GUESS, numberOfTries);
        numberGuessed = 1;
    }
    return numberGuessed;
}

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
            numberGuessed = compareNumbers (randomNumber, guessedNumber, numberOfTries);
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

