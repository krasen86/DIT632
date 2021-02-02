/* ====================================
File name: exerc_2_7.c (or cpp)
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
#include "ctype.h"

// Define section
#define SIZE_PERSONAL_NUMBER 10 // define size of personal number in format yymmddxxxx
#define SIZE_USER_INPUT 64 // accepted size of user input
#define CORRECT_NUMBER_MESSAGE "You entered a valid personal number.\n"
#define WRONG_NUMBER_MESSAGE "You entered an invalid personal number.\n"
#define WRONG_PARAMETERS_MESSAGE "The number you entered was not in format <yymmddxxxx>\n"
#define PROMP_INPUT_MESSAGE "Enter a personal number in format <yymmddxxxx>. To exit the program enter <q>\n"
#define EXIT_MESSAGE "Thank you for using the application.\n"
#define EXIT_CHAR 'q'
#define TRUE 1      // Define true
#define FALSE 0     // Define false
#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define MAY 5
#define JULY 7
#define AUGUST 8
#define OCTOBER 10
#define DECEMBER 12

/* ==================================== Main program section ====================================== */
/* This program TODO ..... */

// Function declaration

int readPersonalNumber( char *person); // Used to read user input
int controlDigit( const char * persnr); // check if the last digit of a given number is valid
int controlDate(char *person); // used to check if the date is valid
int inputValidationInteger(char *input); // checks if the input was integer numbers
int checkLeapYear(int year); // check if a given year is leap
int castToInt(char c); // cast a char to integer


int main() {
    // Variable declarations
    char personalNumber[SIZE_PERSONAL_NUMBER]; // used to store the p-number
    int keepReading = FALSE; // boolean to control the main loop
    keepReading = readPersonalNumber(personalNumber); // call function to read user input
    // Main loop the loop runs while the user doesn't input "q" than the read method returns false and the loop is terminated
    while (keepReading) {
        if(controlDate(personalNumber)) { // call method to verify that the number contains a valid year-month-day in the first 6 positions
            if (controlDigit(personalNumber)) { // call method to check if the last digit is a valid control digit
                printf(CORRECT_NUMBER_MESSAGE); // if valid confirm
            } else {
                printf(WRONG_NUMBER_MESSAGE); // if control digit is wrong notify user
            }
        } else { // if not a valid date print wrong number message to user
            printf(WRONG_NUMBER_MESSAGE);
        }
        keepReading = readPersonalNumber(personalNumber); // call function to continue reading personal number from user again
    }
    printf(EXIT_MESSAGE); // Print goodbye message
    return 0; // Exit the program
}

//----------Functions Section------------

// function used to read user input. The function keeps asking for input until it doesn't get 10 integer numbers
int readPersonalNumber(char *person) {
    printf(PROMP_INPUT_MESSAGE); // ask user for input
    char input[SIZE_USER_INPUT]; // store input
    fgets(input,SIZE_USER_INPUT, stdin); // read input from buffer and store it in the array
    if(input[0] == EXIT_CHAR && strlen(input) == 2 ){ // check if the user has entered exit_char
        return FALSE; // return false when exit char is received in order to terminate the main loop
    }else if(strlen(input) != SIZE_PERSONAL_NUMBER + 1 || !inputValidationInteger(input)) { // if the user has not entered valid amount of char
                                                                                            // call method to verify if it's integer input
                                                                                            // if the method returns false(not integers present in array)
        printf(WRONG_PARAMETERS_MESSAGE);                                                   // notify user for wrong input
        readPersonalNumber(person);                                                         // use recursion to keep reading input
    }else { // Else input is right size and all integers
        strcpy(person, input); // copy input from the array into the main store array
        return TRUE; // return true to main - keeps the main loop running
    }
    return FALSE; // if something is wrong return false to terminate the main loop
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

int controlDate(char *person) {

    int year, month, day;
    long personalNumber;
    char *pointer;

    personalNumber = (long) strtol(person, &pointer, 10);

    year = (int) (personalNumber / 100000000) % 100;
    month = (int) (personalNumber / 1000000) % 100;
    day = (int) (personalNumber / 10000) % 100;

    if ((month > 0 && month <= 12)) {
        if(month == JANUARY || month == MARCH ||month == MAY ||month == JULY || month == AUGUST || month == OCTOBER || month == DECEMBER) {
            if (day > 0 && day <= 31) {
                return TRUE;
            }
        } else {
            if ( month == FEBRUARY) {
                if (!checkLeapYear(year)) {
                    if (day > 0 && day <= 28) {
                        return TRUE;
                    }
                } else {
                    if (day > 0 && day <= 29) {
                        return TRUE;
                    }
                }
            } else { // APRIL, JUNE, SEPTEMBER, NOVEMBER
                if (day > 0 && day <= 30) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

int checkLeapYear(int year) {

    if (((year % 4 == 0) && (year % 100!= 0)) || (year % 400 == 0)) {
        return TRUE;
    }

    return 0;
}

int controlDigit(const char *persnr) {
    // 8112289874 6709199530 TODO remove
    int i;
    long totalSum = 0;
    long sumOfNumber = 0;
    long firstDigitOfTheSumOfNumber = 0;
    long secondDigitOfTheSumOfNumber = 0;

    for (i = 0; i < SIZE_PERSONAL_NUMBER - 1; i++){
        if (i % 2 == 0) {
            sumOfNumber = castToInt(persnr[i]) * 2;
            if (sumOfNumber > 9){
                firstDigitOfTheSumOfNumber = (sumOfNumber / 10) % 10;
                secondDigitOfTheSumOfNumber = sumOfNumber % 10;
                totalSum += firstDigitOfTheSumOfNumber + secondDigitOfTheSumOfNumber;
            } else {
                totalSum += (sumOfNumber * 1);
            }
        } else {
            totalSum += castToInt(persnr[i]);
        }
    }

    if (((10 - (totalSum % 10)) % 10) == castToInt(persnr[SIZE_PERSONAL_NUMBER - 1])) {
        return TRUE;
    }

    return FALSE;
}

int castToInt(char c) {
    int num = 0; // define the int to be return
    num = c - '0'; // subtract '0' from entered char to get the corresponding integer
    return num; // return the integer
}
