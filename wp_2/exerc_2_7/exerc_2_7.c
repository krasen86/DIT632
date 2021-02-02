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
#define SIZE_PERSONAL_NUMBER 10
#define SIZE_USER_INPUT 64
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
/* This program ..... */

// Function declaration

int readPersonalNumber( char *person);
int controlDigit( const char * persnr);
int controlDate(char *person);
int inputValidation(char *input);
int checkLeapYear(int year);
int castToInt(char c);


int main() {
    // Variable declarations
    char personalNumber[SIZE_PERSONAL_NUMBER];
    int keepReading = FALSE;
    keepReading = readPersonalNumber(personalNumber);
    while (keepReading) {
        if(controlDate(personalNumber)) {
            if (controlDigit(personalNumber)) {
                printf(CORRECT_NUMBER_MESSAGE);
            } else {
                printf(WRONG_NUMBER_MESSAGE);
            }
        } else {
            printf(WRONG_NUMBER_MESSAGE);
        }
        keepReading = readPersonalNumber(personalNumber);
    }
    printf(EXIT_MESSAGE); // Print goodbye message
    return 0; // Exit the program
}

//----------Functions Section------------

int readPersonalNumber(char *person) {
    printf(PROMP_INPUT_MESSAGE);
    char input[SIZE_USER_INPUT];
    fgets(input,SIZE_USER_INPUT, stdin);
    if(input[0] == EXIT_CHAR && strlen(input) == 2 ){
        return FALSE;
    }else if(strlen(input) != SIZE_PERSONAL_NUMBER + 1 || !inputValidation(input)) {
        printf(WRONG_PARAMETERS_MESSAGE);
        readPersonalNumber(person);
    }else {
        strcpy(person, input);
        return TRUE;
    }
    return FALSE;
}

int inputValidation(char *input) {
    while (*input) {
        if(*input != '\n') {
            if (isdigit(*input) == 0) {
                return FALSE;
            }
        }
        input++;
    }
    return TRUE;
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
    // 8112289874 6709199530
    int i;
    int sum = 0;
    long temp1 = 0, temp2 = 0, temp3;

    for (i = 0; i < SIZE_PERSONAL_NUMBER - 1; i++){
        if (i % 2 == 0) {
            temp1 = castToInt(persnr[i]) * 2;
            if (temp1 > 9){
                temp2 = (temp1 / 10) % 10;
                temp3 = temp1 % 10;
                sum += temp2 + temp3;
            } else {
                sum += temp1;
            }
        } else {
            sum += castToInt(persnr[i]);
        }
    }

    if (((10 - (sum % 10)) % 10) == castToInt(persnr[SIZE_PERSONAL_NUMBER - 1])) {
        return TRUE;
    }

    return FALSE;
}

int castToInt(char c) {
    int num = 0;

    //Substract '0' from entered char to get
    //corresponding digit
    num = c - '0';
    return num;
}
