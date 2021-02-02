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
#define WRONG_PARAMETERS_MESSAGE "Please enter a person number in format <yymmddxxxx>\n"
#define PROMP_INPUT_MESSAGE "Enter a personal number in format <yymmddxxxx>. To exit the program enter <q>\n"
#define EXIT_MESSAGE "Thank you for using the application.\n"
#define EXIT_CHAR 'q'
#define TRUE 1      // Define true
#define FALSE 0     // Define false

/* ==================================== Main program section ====================================== */
/* This program ..... */

// Function declaration

void readPersonalNumber( char *person);
int controlDigit( const char * persnr);
void controlDate(char *person);
int inputValidation(char *input);

int main() {
    // Variable declarations
    char personalNumber[SIZE_PERSONAL_NUMBER];
    readPersonalNumber(personalNumber);

    while (personalNumber[0] != EXIT_CHAR || strlen(personalNumber) != 2) {
        if(controlDate(personalNumber)) {
            if (controlDigit(personalNumber)) {
                printf(CORRECT_NUMBER_MESSAGE);
            } else {
                printf(WRONG_NUMBER_MESSAGE);
            }
        }
        readPersonalNumber(personalNumber);
    }
    return 0; // Exit the program
}

//----------Functions Section------------

void readPersonalNumber(char *person) {
    printf(PROMP_INPUT_MESSAGE);
    char input[SIZE_USER_INPUT];
    fgets(input,SIZE_USER_INPUT, stdin);
    if(input[0] == EXIT_CHAR && strlen(input) == 2 ){
        printf(EXIT_MESSAGE);
        exit(0);
    }else if(strlen(input) != SIZE_PERSONAL_NUMBER + 1 || !inputValidation(input)) {
        printf(WRONG_PARAMETERS_MESSAGE);
    }else {
        strcpy(person, input);
    }

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

void controlDate(char *person) {

}

int controlDigit(const char *persnr) {
    return 0;
}
