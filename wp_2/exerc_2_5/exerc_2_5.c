/* ====================================
File name: exerc_2_5.c (or cpp)
Date: 2021-02-04
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: 5202
====================================== */

// Include section
#include "stdio.h"
#include <stdlib.h>
#include <time.h>
// Define section
#define MAX 100 // total numbers in array
#define MAX_NUMBER 20 // range for random number used to populate the array
#define END_OF_LINE '\n' // define end of line
#define FREQUENCY_SYMBOL "x" // display number of frequency with x

// ------ Function declaration ----------
void create_random( int *tab );
void count_frequency(const int *tab, int *freq ); // Use pointer
void draw_histogram(const int *freq );

/* ==================================== Main program section ====================================== */
/* This program generates a random number array given a range of numbers and than checks for the repeated frequency of the numbers.
 * Once the frequency is counted it is displayed to the user.*/

int main (){
    // Variable declarations
    int table[MAX]; // store random numbers
    int frequency[MAX_NUMBER]; // store frequency of the random numbers

    create_random(table); // call function to populate table with random numbers
    count_frequency(table, frequency); // call function to populate the frequency array with the repeated number count
    draw_histogram(frequency); // display the numbers and the number of repeating
    return 0; // Exit the program
}

//----------Functions Section------------

// Function for generating random numbers and adding them to the table array
void create_random(int *tab ) {
    srand(time(0)); // Generate seed for the creation of random numbers based on time function
    for (int i = 0; i < MAX; i++) { // iterate in the array
        *tab = rand() % (MAX_NUMBER+1); // generate a new "random" number by using the rand() function, numbers is between 0 and MAX_NUMBER
        tab++; // increment the pointer
    }
}
//Function for counting the frequency of the numbers in an array and saving that frequency in an array
void count_frequency(const int *tab, int *freq ){
    int i = 0; // index
    int counter = 0; // keep track of frequency for number
    int j = 0; // index inner loop
    for (i = 0; i <= MAX_NUMBER; i++) { // Iterate through all possible numbers
        for (j = 0; j < MAX; j++) { // for each number go over the the array with random numbers
            if (tab[j] == i) { // if a number is present in the array
                counter++; // increment the counter
            }
        }
        *freq = counter; // assign the counter to the corresponding frequency array position
        freq++; // increment the frequency pointer
        counter = 0; // reset the counter for the next loop iteration
    }
}
// Function used to display the frequency of the numbers
void draw_histogram(const int *freq) {
    int i = 0; // index
    int frequency = 0; // frequency count
    for (i = 0; i <= MAX_NUMBER; ++i) { // iterate over the possible numbers
        if(*freq > 0) // if the corresponding frequency array position contains positive value
        {
            printf("%d ", i); // display the number associated with the value
            frequency = *freq; // get the frequency value from the pointer array
            while (frequency != 0) { // loop until the frequency is not back to 0
                printf(FREQUENCY_SYMBOL); // display the frequency symbol
                frequency--; // decrement the frequency
            }
            printf("%c",  END_OF_LINE); // complete the printing with new line
        }
        freq++; // increment the pointer
    }
}

