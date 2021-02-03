/* ====================================
File name: exerc_2_8.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include <string.h>


#define MAX_COINS 13
#define READ_HUMAN_CHOICE "Human, you're up:\n"
#define SIZE_USER_INPUT 10
#define SENTENCE_WRONG_INPUT "Not valid, please try again \n" // Invalid input prompt
#define EXIT_CHAR 'q' // Character for exiting the program
#define EXIT_MESSAGE "Exiting the Nim game...\n"
#define LOWER_INVALID_INPUT 0 // Lower integer threshold for an invalid input
#define UPPER_INVALID_INPUT 4 // Upper integer threshold for an invalid input

const int HUMAN = 0;
const int COMPUTER = 1;

/* ------------- IO --------------- */

/*
 * human_choice
 * Get human choice as an int from stdin.
 * Clears stdin.
 * in: pile
 * out: int-value in range 1-3 (and also less than pile)
 */
int human_choice(int pile);

/*
 * write_winner
 * Write winner as a string on stdout.
 * in: Values HUMAN or COMPUTER.
 * out:
 */
void write_winner( int player );

/*
 * play_again
 * Ask human if he/she wants to play
 * another round. If 'n' or 'N' selected
 * (single char) return false else true.
 * Clears stdin.
 * in:
 * out: true or false
 */
int play_again();

/* ---------------- Logic ----------------*/

/*
 * computer_choice
 * Get computers choice (including some AI,
 * if 4 coins or less left, function makes a
 * smart choice else random).
 * in: pile
 * out: int-value in range 1-3 (and also less than pile)
 */
int computer_choice(int pile);

/*
 * toggle
 * Switches player, if HUMAN in COMPUTER out
 * etc.
 * in:  actual player
 * out: next player
 */
int toggle( int player );

/* --------------------- Utilities -------------*/
void clear_stdin();

/***************************************************
 *
 *    MAIN
 *
 ***************************************************/
int main()
{
    int pile,			/* This is how many coins we have */
    player,			/* Who is playing? */
    n_coins;			/* Number of coins taken */

    srand( time(0) );		/* Setup random */

    printf("Welcome to Nim game...");



    pile = MAX_COINS;		/* Set start values (= init) */
    player = HUMAN;

    /*
     *  Program main loop
     */
    while( true ) {

        printf("There are %d  coins in the pile\n", pile );

        if( player == HUMAN ){
            n_coins = human_choice(pile);
        }else{
            n_coins = computer_choice(pile);
            printf("- I took %d\n", n_coins);
        }
        pile -= n_coins;
        player = toggle( player );

        if( pile <= 1 ){
            break;
        }
    }
    /*
     * end main loop
     */

    write_winner( player );


    printf("Terminating...\n");

    return 0;
}

/******************************************************
 *
 *  DEFINITIONS
 *
 ******************************************************/


void clear_stdin()
{
    while( getchar() != '\n');
}

int human_choice(int pile)
{
    char input[SIZE_USER_INPUT];
    int inputNumber;
    do {
        printf(READ_HUMAN_CHOICE);
        fgets(input,SIZE_USER_INPUT, stdin); // read input from buffer and store it in the array

        if (sscanf(input, "%d", &inputNumber) == 1 && strlen(input) == 2) {   // Read integers from the stored character array
            if (inputNumber < pile) {
                if (inputNumber > LOWER_INVALID_INPUT && inputNumber < UPPER_INVALID_INPUT) {
                    return inputNumber;
                } else {
                    printf(SENTENCE_WRONG_INPUT);
                }
            } else {
                printf(SENTENCE_WRONG_INPUT);
            }
        } else {
            if (input[0] == EXIT_CHAR && strlen(input) == 2) {
                printf(EXIT_MESSAGE);
                exit(0);
            } else {
                printf(SENTENCE_WRONG_INPUT);
            }
        }

        clear_stdin();
    } while (true);
}

int computer_choice(int pile)
{

    return 0;
}

void write_winner(int player )
{

}

int play_again()
{

    return 0;
}

int toggle( int player )
{

    return 0;
}

