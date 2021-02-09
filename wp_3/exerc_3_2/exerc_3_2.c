/* ====================================
File name: exerc_3_2.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stdio.h"

// Define section
#define NOT_FOUND (-1) // use for when number is not present in array
#define NOT_FOUND_MESSAGE "Number not found in array\n" // used to notify when number is not present
#define FOUND_MESSAGE "Number found in array at position %d.\n" // used to confirm that the number is present and print the position
#define PROMP_INPUT_MESSAGE "Please enter a number. To exit press <q>\n" // String used to ask user for input
#define EXIT_MESSAGE "Thank you for using the application\n" // Goodbye message
#define WRONG_PARAMETERS_MESSAGE "Not a valid input please try again..\n"
#define ARRAY_STATE "Current state of the numbers in the array " // string printed before starting to print the array
#define EXIT_CHAR 'q' // exit char represents quit
#define SIZE_USER_INPUT 20 // max size accepted for user input
#define TRUE 1      // Define true
#define FALSE 0     // Define false
#define EXIT_INPUT_READ (-1) // invalid input
#define START_SORT_MESSAGE "Sorting the array list\n" // string to display when the sort method is called

/* ==================================== Main program section ====================================== */
/* This program TODO.....
*/
// Function declaration
int search_number( int number, int tab[], int size);
int readNumber();
int inputValidationInteger(char *input);
void printList(int *list, int size);
void sort (int number, int tab []);

int main() {
    // Variable declarations
    int test [] = { 1,2,34,5,67,3,23,12,13,10}; // test numeric array
    int number; // store the number read from the user
    int position; // store position of the found number
    number = readNumber(); // call function to read user input
    int size = sizeof(test)/sizeof(test[0]); // calculate and store the length of the test array
    if (number == EXIT_INPUT_READ) { // if the result of readNumber is exit char
        printf(EXIT_MESSAGE); // print exit message
        return 0; // exit the programme
    }
    position = search_number(number, test, size); // call search method to get the position of a given number
    if (position == NOT_FOUND) { // if the number is not found, the return was NOT_FOUND
        printf(NOT_FOUND_MESSAGE); // notify the user that the number was not found
    } else { // if the number is present
        printf(FOUND_MESSAGE, position); // print the position of the number in the array
    }
    printList(test, size); // call a function to print the integers in the list
    printf(START_SORT_MESSAGE); // notify the start of sorting
    sort(size, test); // call sort method
    printList(test, size); // print the sorted array
    printf(EXIT_MESSAGE);  // print exit message
    return 0; // Exit the program
}

// function used to read user input. The function keeps asking for input until it doesn't get integer number
int readNumber() {
    char input[SIZE_USER_INPUT]; // store input
    int keepReading = TRUE; // set boolean for reading input
    while (keepReading) { // start the reading input loop
        printf(PROMP_INPUT_MESSAGE); // ask user for input
        fgets(input,SIZE_USER_INPUT, stdin); // read input from buffer and store it in the array
        if(input[0] == EXIT_CHAR && strlen(input) == 2){ // check if the user has entered exit_char and the the input is size of 2
            return EXIT_INPUT_READ; // return invalid input read
        }else if(input[0] == '\n' || !inputValidationInteger(input)) {  //check if there is call method to verify if it's integer input
            // if the method returns false(not integers present in array)
            printf(WRONG_PARAMETERS_MESSAGE);// notify user for wrong input
        }else { // Else input is right size and all integers
            keepReading = FALSE; // break the reading input loop
        }
    }
    char *pointer; // pointer needed for the strtol function (the pointer stores the non numeric part of the char array that is to be converted)
    return (int) strtol(input, &pointer, 10); // Converting the char array to a base(10) long using strtol() end return it
}

// Function to validate if a given string consists of only integers
int inputValidationInteger(char *input) {
    while (*input) { // loop in the array using the pointer
        if(*input != '\n') { // ignore the end of line for the comparison
            if (isdigit(*input) == 0) { // check if the char is not digit isdigit function
                return FALSE; // if not digit return false
            }
        }
        input++; // increment the pointer
    }
    return TRUE; // if the loop run without encountering char return true
}
// The function used to to check if a given number is in the array,
// if the number is not in the array it returns NOT_FOUND else returns the position
int search_number(int number, int tab[], int size){
    int i; // index for array
    for (i = 0; i < size; i++) { // triverse the array
        if (tab[i] == number) { // if the number in the position is equal to the provided number
            return i; // return the position
        }
    }
    return NOT_FOUND; // if the loop has run and the number is not present return NOT_FOUND
}
// Sort the array if int given, number represents the size of the array
void sort (int number, int tab []){
    int i; // index for array
    int j; // index for inner loop
    int minPosition; // store the min number position
    int tempNumber; // store number for swapping
    for (i = 0; i < number; i++) { // outer loop traverse the array
        minPosition = i; // set the index for the min number
        for (j = i + 1; j < number; j++) { // start inner loop for every single number
            if (tab[j] < tab[minPosition]) { // check if the next number to the end is smaller to the set min position
                minPosition = j; // if smaller change the minPosition index to point to the smaller number
            }
        }
        if (i != minPosition) { // after the inner loop has run check if the current index is not the same as the minPosition (a smaller number has be found)
            tempNumber = tab[i]; // store the number in the index for swapping
            tab[i] = tab[minPosition]; // store the smaller number found in the current index
            tab[minPosition] = tempNumber; // store the old value of index at the position where the old smaller number was (swap)
        }
    }
}
// Function used to print the array's integer
void printList(int *list, int size) {
    printf(ARRAY_STATE); // display starting to print
    int i; // index for array
    for(i = 0; i < size; i++) {
        printf("|%d ", list[i]); // iterate over the list and print every number
    }
    printf("\n"); // finish with new line
}
