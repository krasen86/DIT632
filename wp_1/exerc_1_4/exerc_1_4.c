#include "stdio.h"
#include <time.h>
#include <stdlib.h>
#include "string.h"

#define MAX_NUMBER 5
#define INITIAL_PROMPT "Guess a number between 1-100\n"
#define GUESS_LOW "Guess is too low, number of tries: %d\n"
#define GUESS_HIGH "Guess it too high, number of tries: %d\n"
#define CORRECT_GUESS "You guessed correct! Total number of tries was %d \n"
#define FAIL_GUESS "Sorry you ran out of tries!\n"
#define PLAY_AGAIN "Would you like to play again? (y/n)?\n"

int main() {
    do {
        char answer[32];
        char answerChar;
        int numberGuessed = 0;
        srand(time(NULL));
        int randomNumber = rand() % 100 + 1;
        char guess[32];
        int guessedNumber;
        int numberOfTries = 1;

        printf("%d\n", randomNumber);
        printf(INITIAL_PROMPT);
        do{
            fgets(guess, sizeof (guess), stdin);
            sscanf(guess, "%d", &guessedNumber);

            if(guessedNumber<randomNumber) {
                printf(GUESS_LOW, numberOfTries);
            }else if(guessedNumber>randomNumber) {
                printf(GUESS_HIGH, numberOfTries);
            }else {
                printf(CORRECT_GUESS, numberOfTries);
                numberGuessed = 1;
                break;
            }
            numberOfTries++;
        }while(guessedNumber != randomNumber && numberOfTries <= MAX_NUMBER);

        if(!numberGuessed) {
            printf(FAIL_GUESS);
        }

        printf(PLAY_AGAIN);
        fgets(answer, sizeof (answer), stdin);
        sscanf(answer, "%c", &answerChar);

        if(answerChar != 'y' || strlen(answer) > 2) {
            return 0;
        }

    } while (1);

}

