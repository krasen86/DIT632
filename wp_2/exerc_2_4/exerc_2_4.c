/* ====================================
File name: exerc_2_4.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <string.h>
#include <stdlib.h>
#include "stdio.h"

// Define section
#define MAX_LENGTH 50 // maximum char accepted for a string including end of string
#define INPUT_MESSAGE "Please enter a string (up to 50 char)....\n" // prompt message for user input
#define IS_PALINDROME_MESSAGE "The given strings: %s, is a palindrome.\n" // display that the string is a palindrome
#define IS_NOT_PALINDROME_MESSAGE "The given strings: %s, is NOT a palindrome.\n" // display that the string is not a palindrome
#define NO_STRING_PROVIDED "You need to provide a string, please restart the programme....." // error message for handling no input
#define FALSE 0 // define boolean false
#define TRUE 1 // define boolean true
#define END_OF_STRING '\0' // define end of string
#define END_OF_LINE '\n' // define end of line

/* ==================================== Main program section ====================================== */
/* This program reads a string from the command line and checks if it's palindrome or not and displays the result.
 * The programme doesn't handle spaces or multiple strings. It has basic error handling if user presses enter without entering anything, than the programme stops.*/

// Function declaration
int checkIfPalindrome(const char givenString[], unsigned int length); // check if a given string is palindrome

int main() {
    // Variable declarations
    char givenString[MAX_LENGTH]; // store string
    int isPalindrome = FALSE; // store result of palindrome check

    printf(INPUT_MESSAGE); // Promp user for input
    fgets(givenString, MAX_LENGTH, stdin); // read from buffer and store in the char array
    if (givenString[strlen(givenString) - 1] == END_OF_LINE) { // check if new line is present
        givenString[strlen(givenString) - 1]  = END_OF_STRING ; // replace new line with string end
    }
    if (givenString[0] == END_OF_STRING ) { // Check if input is "empty" string - case when user just presses enter
        printf(NO_STRING_PROVIDED);
        return 0; // Exit the program
    }
    isPalindrome = checkIfPalindrome(givenString, strlen(givenString)); // call function to check if the string is palindrome by providing the length
    if (isPalindrome) {  // check if palindrome
        printf(IS_PALINDROME_MESSAGE, givenString); // display string is palindrome
    } else {
        printf(IS_NOT_PALINDROME_MESSAGE, givenString); // display string is not palindrome
    }
    return 0; // Exit the program
}

// The function checks if a given char array string is a palindrome or not and returns the result
int checkIfPalindrome(const char givenString[], unsigned int length) {
    unsigned int endOfString = length - 1; // define the end index of string by length removing the end of string
    int startOfString = 0; // define the start of string index
    while (endOfString > startOfString) { // loop while the middle is not reached
        if (givenString[startOfString] != givenString[endOfString]) { //compare the ends going inwards
            return FALSE;  // return false if not same
        }
        endOfString--; // decrement the end index
        startOfString++; // increment the start index
    }
    return TRUE; // return true if the loop has run successfully
}

