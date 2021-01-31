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

// Define section
#define SIZE_PERSONAL_NUMBER 10
#define CORRECT_NUMBER_MESSAGE "You entered a valid personal number.\n"
#define WRONG_NUMBER_MESSAGE "You entered an invalid personal number.\n"
#define PROMP_INPUT_MESSAGE "Enter a personal number in format <yymmddxxxx>. To exit the program enter <q>\n"
#define EXIT_MESSAGE "Thank you for using the application.\n"
#define EXIT_CHAR 'q'

/* ==================================== Main program section ====================================== */
/* This program ..... */

// Function declaration

void readPersonalNumber( char *person);
int controlDigit( const char * persnr);


void controlDate(char *person);

int main() {
    // Variable declarations
    char personalNumber[SIZE_PERSONAL_NUMBER];
    readPersonalNumber(personalNumber);
    if (personalNumber[0] == EXIT_CHAR) {
        printf(EXIT_MESSAGE);
        return 0;
    }
    if (controlDigit(personalNumber)) {
        printf(CORRECT_NUMBER_MESSAGE);
    } else {
        printf(WRONG_NUMBER_MESSAGE);
    }
    return 0; // Exit the program
}

//----------Functions Section------------

void readPersonalNumber(char *person) {
    do {
        printf(PROMP_INPUT_MESSAGE);
        fgets(person,SIZE_PERSONAL_NUMBER+1, stdin);
    } while (person[0] != EXIT_CHAR || strlen(person) != 2);
}

void controlDate(char *person) {

}

int controlDigit(const char *persnr) {
    return 0;
}
