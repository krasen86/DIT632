/* ====================================
File name: exerc_2_8.c (or cpp)
Date: 2021-02-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: 5202
====================================== */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include <string.h>

#define MAX_COINS 13 // Maximum number of coins in the pile
#define READ_HUMAN_CHOICE "Human, you're up! Please enter a number between 1-3:\n" // String to be prompted to the user of entering a number
#define SIZE_USER_INPUT 10 // Used to set the size of the array for the user's input
#define SENTENCE_WRONG_INPUT "Not valid, please try again \n" // Invalid input prompt
#define EXIT_CHAR 'q' // Character for exiting the program
#define EXIT_MESSAGE "Exiting the Nim game...\n" // String to be printed when exiting the game
#define LOWER_VALID_INPUT 1 // Lower integer threshold for an invalid input
#define UPPER_VALID_INPUT 3 // Upper integer threshold for an invalid input
#define RANDOM_NUMBER_THRESHOLD 4 // The threshold used when creating a random number
#define COMPUTER_VICTORY "Computer won the game!\n" // String to be printed when computer won the game
#define HUMAN_VICTORY "You have won the game!\n" // String to be printed when the human won the game
#define PLAY_AGAIN "Would you like to play again? y/n\n" // String for prompting the user whether they want to continue playing another round
#define RESPOND_YES 1 // Returned value when the user wants to play another round
#define RESPOND_NO 0 // Returned value when the user does not want to play another round
#define WELCOME_MESSAGE "Welcome to Nim game...\n" // String to be printed in order to welcome the user to the game
#define NUMBER_OF_COINS_IN_PILE "There are %d coins in the pile\n" // String to print the number of coins that there are currently in the pile
#define COMPUTER_RESPONSE "Computer took %d coins\n\n" // String to notify the user how many coins the computer took in the current round

const int HUMAN = 0; // Constant number that defines the human player
const int COMPUTER = 1; // Constant number that defines the computer

/* ==================================== Main program section ====================================== */
/* This is an implementation of the Nim game. Two players take in turn between one and three coins
 * from the stack. Whoever are forced to take the last coin have lost. The program allows quitting
 * at any step by inputting 'q'.
 * */

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

    printf(WELCOME_MESSAGE); // printing a welcome message to the user

    /*
     *  Program main loop
     */
    do {
        pile = MAX_COINS; // initialize the number of coins in the pile to the max value
        player = HUMAN; // start with the human as the first player
        while (pile > 1) { // iterate while there are more than 1 coins in the pile

            printf(NUMBER_OF_COINS_IN_PILE, pile); // notifying of the current state of the pile

            if (player == HUMAN) { // Check if it's the human's turn
                n_coins = human_choice(pile); // Storing the user's choice of amount of coins
            } else { // Computer's turn
                n_coins = computer_choice(pile); // Storing the computer's choice of amount of coins
                printf(COMPUTER_RESPONSE, n_coins); // Notifying the user of the amount of coins that the computer took
            }
            pile -= n_coins; // update the pile based on the X amount of coins that have been taken in this round
            player = toggle(player); // switch the player to the other one for the next round
        }
        write_winner( player ); // Display the winner after finishing all the rounds
    } while (play_again()); // Call a function to see if the user wants to continue playing
    /*
     * end main loop
     */

    printf(EXIT_MESSAGE); // Displaying the exit message to the user

    return 0; // exit the program
}

/******************************************************
 *
 *  DEFINITIONS
 *
 ******************************************************/

// Function to clear the stdin buffer
void clear_stdin() {
    while( getchar() != '\n' ); // iterate and empty the buffer until the EOF character is found
}

// Function to read and process the user's choice
int human_choice(int pile)
{
    // Variables declarations
    char input[SIZE_USER_INPUT]; // store the user's input
    int inputNumber; // store the integer representation of the input

    do {
        printf(READ_HUMAN_CHOICE); // prompt the user to enter a value
        fgets(input,SIZE_USER_INPUT, stdin); // read input from buffer and store it in the array

        if (strlen(input) == (SIZE_USER_INPUT-1) && input[SIZE_USER_INPUT-1] == '\0' ){ // Check if the input array is full
            clear_stdin(); // call function to clear the buffer
        }
        if (sscanf(input, "%d", &inputNumber) == 1 && strlen(input) == 2) {   // Read integers from the stored character array
                                                                                     // Check if the input contains an integer value
                                                                                     // Check if the stored character array is not of size 2 (including \n)
            if (inputNumber < pile) { // check if the user's input is less than the current amount of coins in the pile
                if (inputNumber >= LOWER_VALID_INPUT && inputNumber <= UPPER_VALID_INPUT) { // check if the user's input is within the valid interval
                    return inputNumber; // return user's input
                } else { // user's choice was out of bounds
                    printf(SENTENCE_WRONG_INPUT); // notify the user that the input is incorrect
                }
            } else { // the input number is larger than the pile
                printf(SENTENCE_WRONG_INPUT); // notify the user that the input is incorrect
            }
        } else { // handle alphabetical input
            if (input[0] == EXIT_CHAR && strlen(input) == 2) { // check if the EXIT_CHAR has been entered
                printf(EXIT_MESSAGE); // print the exit message
                exit(0); // exit the program
            } else { // handle all the other invalid input
                printf(SENTENCE_WRONG_INPUT); // notify the user of invalid input
            }
        }
    } while (true); // keep prompting the user for input
}

// Function to calculate the computer's choice
int computer_choice(int pile)
{
    // Variables declarations
    int computerChoice; // store the number of coins for the computer's choice

    if(pile > RANDOM_NUMBER_THRESHOLD) { // check if the pile is larger than the threshold
        computerChoice = rand() % (UPPER_VALID_INPUT) + LOWER_VALID_INPUT; // calculate a random number between the accepted bounds and store it to a variable
        return computerChoice; // return the computer's choice
    }else { // the pile is less or equal to the RANDOM_NUMBER_THRESHOLD
        computerChoice = pile - 1; //  taking every coin except the last one so that computer wins
        return computerChoice; // return the computer's choice
    }
}

// Function to display the winner of the game to the user
void write_winner(int player )
{
    if(player == COMPUTER){ // check if the last player was the computer
        printf(HUMAN_VICTORY); // display a message for human's victory
    }else { // the last player was the human
        printf(COMPUTER_VICTORY); // display a message for computers's victory
    }
}

// Function to prompt the user if they want to play again
int play_again()
{
    // Variables declarations
    char input; // store the user's input

    printf(PLAY_AGAIN); // prompt the user with a message asking if they want to play again
    input = getc(stdin); // read user's answer

    if(input == 'y' || input == 'Y') { // covers the case that the user wants to play again
        clear_stdin(); // call the method to clear the buffer
        return RESPOND_YES; // return user's response
    }else if(input == 'n' || input == 'N'){ // covers the case that the user does not want to play again
        clear_stdin(); // call the method to clear the buffer
        return RESPOND_NO; // return user's response
    }else { // covers the case of invalid input entered by the user
        printf(SENTENCE_WRONG_INPUT); // notify the user of invalid input
        clear_stdin(); // call the method to clear the buffer
        return play_again(); // recursive call to prompt the user again for a valid input
    }
}

// Function to switch between users in order to change their turn
int toggle( int player )
{
    player = !player; // switching the currentl player to the other one
    return player; // return the new player
}