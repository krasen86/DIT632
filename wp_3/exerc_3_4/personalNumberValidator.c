/* This file's purpose is to validate a given personal number in a string format
 * by verifying whether the date is within the valid bounds and the control digit
 * is valid by checking it using the Luhn algorithm. The validation works with both
 * 10-digit and 12-digit personal numbers.
 *
 * Disclaimer: The following code had been mostly written for the purpose of Exercise
 * 2.3, and therefore since the solution of Exercise 3.4 requires personal number
 * validation, it has been used, partially revised and provided as a library in order
 * to extend the functionality of the implementation in Ex. 3.4.
 */

// Include section
#include <string.h>
#include <stdlib.h>
#include "ctype.h"
#include "personalNumberValidator.h"


// Define section
#define MAX_SIZE_PERSONAL_NUMBER 13 // define the maximum size of personal number
#define TRUE 1      // Define true
#define FALSE 0     // Define false
#define JANUARY 1   // Value representing January
#define FEBRUARY 2  // Value representing February
#define MARCH 3     // Value representing March
#define MAY 5       // Value representing May
#define JULY 7      // Value representing July
#define AUGUST 8    // Value representing August
#define OCTOBER 10  // Value representing October
#define DECEMBER 12 // Value representing December

int inputValidationInteger(char *input); // checks if the input was integer numbers
int controlDate(char *person); // used to check if the date is valid
int controlDigit(const char *persnr); // check if the last digit of a given number is valid
int checkLeapYear(int year); // check if a given year is leap
int getIntegerValue(char c); // convert a char to integer

// Implementation of the interface-defined function to validate the provided personal number
int validatePersonalNumber(char *input) {

    if (inputValidationInteger(input)) { // check if the provided input contains only integers
        if (controlDate(input)) { // validates if the date of the given personal number is within allowed bounds
            return controlDigit(input); // checks if the control digit is calculated correctly based on the Luhn algorithm and returns the outcome
        }
    }

    return FALSE; // return false in case the validation is incorrect
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

// Function to validate if the date part of the provided personal number is correct
int controlDate(char *person) {
    // Variable declarations
    int year, month, day; // Store the corresponding year, month and day part based on the provided 6 first digits
    long personalNumber; // Store the personal number using a numeric format
    char *pointer; // pointer needed for the strtol function (the pointer stores the non numeric part of the char array that is to be converted)

    personalNumber = (long) strtol(person, &pointer, 10); // Converting the char array to a base(10) long variable for storing the personal number, using strtol()

    year = (int) (personalNumber / 100000000) % 100; // Casting the first two digits of the provided personal number (long) to an int variable to get the year
    month = (int) (personalNumber / 1000000) % 100; // Casting the 3rd and 4th digits of the provided personal number (long) to an int variable to get the month
    day = (int) (personalNumber / 10000) % 100; // Casting the 5th and 6th digits of the provided personal number (long) to an int variable to get the day

    if ((month > 0 && month <= 12)) { // Check if the month is within a valid interval
        if(month == JANUARY || month == MARCH ||month == MAY ||month == JULY || month == AUGUST || month == OCTOBER || month == DECEMBER) { // Covers the months that have 31 days
            if (day > 0 && day <= 31) { // Check if the day is within the valid interval
                return TRUE; // return true for a valid date
            }
        } else { // Covers all the months that have either 30 days or less
            if ( month == FEBRUARY) { // Covers the case of February
                if (!checkLeapYear(year)) { // Check if the year is not a leap year
                    if (day > 0 && day <= 28) { // Check if the day is within the valid interval
                        return TRUE; // return true for a valid date
                    }
                } else { // Covers the leap year case for February
                    if (day > 0 && day <= 29) { // Check if the day is within the valid interval
                        return TRUE; // return true for a valid date
                    }
                }
            } else { // Covers the months that have 30 days
                if (day > 0 && day <= 30) { // Check if the day is within the valid interval
                    return TRUE; // return true for a valid date
                }
            }
        }
    }

    return FALSE; // Return false for invalid date
}

// Function to validate if the control digit of the provided personal number is correct
int controlDigit(const char *persnr) {

    int i; // index for the loop
    long totalSum = 0; // Store the total sum of the sums of digits
    int controlNumberPosition; // Store the control number's position
    long sumOfNumber = 0; // Store the multiplied value of the corresponding digit
    long firstDigitOfTheSumOfNumber = 0; // Store the first digit of the sum of number when the sumOfNumber is larger than 9
    long secondDigitOfTheSumOfNumber = 0; // Store the second digit of the sum of number when the sumOfNumber is larger than 9

    if (strlen(persnr) == MAX_SIZE_PERSONAL_NUMBER - 1) { // check if the provided personal number consists of 12 digits
        i = 2; // set the index to skip the first two digits from the personal number
        controlNumberPosition = MAX_SIZE_PERSONAL_NUMBER - 2; // set the controlNumberPosition
    } else { // default case, i.e. 10-digits personal number
        i = 0; // set the index
        controlNumberPosition = MAX_SIZE_PERSONAL_NUMBER - 4; // set the controlNumberPosition
    }

    for (i; i < controlNumberPosition; i++){ // iterate through the personal number's characters
        if (i % 2 == 0) { // If its an even position in the array
            sumOfNumber = getIntegerValue(persnr[i]) * 2; // Get integer value of the corresponding char multiplied by 2
            if (sumOfNumber > 9){ // If the resulted number is greater than 9
                firstDigitOfTheSumOfNumber = (sumOfNumber / 10) % 10; // get the first digit of the sum of number
                secondDigitOfTheSumOfNumber = sumOfNumber % 10; // get the second digit of the sum of number
                totalSum += firstDigitOfTheSumOfNumber + secondDigitOfTheSumOfNumber; // add to the totalSum the sum of the two numbers
            } else { // If the resulted number is less or equal than 9
                totalSum += (sumOfNumber); // add the number to the totalSum
            }
        } else { // If its an odd position in the array
            totalSum += getIntegerValue(persnr[i]); // getting the integer value of the currect character in the array and adding it to the totalSum
        }
    }

    if (((10 - (totalSum % 10)) % 10) == getIntegerValue(persnr[controlNumberPosition])) {  // Compare the last digit of the subtraction between 10 minus the last digit of the total sum
                                                                                            // to the last digit of the provided personal number
        return TRUE; // return true if the control digit is correct
    }

    return FALSE; // return false if the control digit is incorrect
}

// Function to calculate if the provided year is a leap year
int checkLeapYear(int year) {

    if (((year % 4 == 0) && (year % 100!= 0)) || (year % 400 == 0)) { // Check if the year follows the leap year calculation pattern
        return TRUE; // return true if it is a leap year
    }

    return FALSE; // return false if it is not a leap year
}

// Function for converting a given char to integer and returning the int
int getIntegerValue(char c) {
    int num = 0; // define the int to be return
    num = c - '0'; // subtract '0' from entered char to get the corresponding integer
    return num; // return the integer
}