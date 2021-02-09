/* ====================================
File name: exerc_3_4.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


// Define section
#define LENGTH_NAME 20
#define LENGTH_PERSONAL_NUMBER 13 // yyyymmddnnnc
#define TRUE 1
#define FALSE 0
#define FILE_NAME "person.bin"
#define FIRST_MENU_CHOICE "1 Create a new and delete the old file.\n"
#define SECOND_MENU_CHOICE "2 Add a new person to the file.\n"
#define THIRD_MENU_CHOICE "3 Search for a person in the file.\n"
#define FOURTH_MENU_CHOICE "4 Print out all in the file.\n"
#define FIFTH_MENU_CHOICE "5 Exit the program.\n"
#define PROMPT_USER_CHOICE "Enter your choice: "
#define MAX_LENGTH_USER_INPUT 100
#define PROMPT_SEARCH_TYPE "Press 1 to search by first name OR Press 2 to search by last name\n"
#define PROMPT_INVALID_CHOICE "That was not a valid input.....\n"
#define TRY_AGAIN_MESSAGE "Try again: "
#define PROMPT_FIRST_NAME "Please enter first name: "
#define PROMPT_LAST_NAME "Please enter last name: "
#define EXIT_MESSAGE "Thank you for using the application\n"
#define PRINT_PERSON_DATA "Person: %s, %s, %s\n"
#define PRINT_DUMMY_RECORD "Dummy record: %s, %s, %s\n"
#define ERROR_OPENING_FILE "Error opening the file and/or file doesn't exists...\n"
#define PERSON_NOT_FOUND_MESSAGE "Person with that name was not found.\n"
#define PERSON_FOUND_MESSAGE "Result %d\nPerson found: %s, %s, %s\n"
#define PROMPT_PERSONAL_NUMBER "Please enter your personal number in format <yyyymmddnnnc>: "
#define ERROR_ALLOCATION "Memory allocation failed. Please try again\n"
#define NO_FILE_MESSAGE "There is currently no file. Please create a file first...\n"

// -----Typedefs -------
typedef struct {
    char firstName[LENGTH_NAME];
    char lastName[LENGTH_NAME];
    char pers_number[LENGTH_PERSONAL_NUMBER];
}PERSON;

const char appendToFileMode[] = "ab";
const char readFromFileMode[] = "rb";
const char writeToFileMode[] = "wb";
/* ==================================== Main program section ====================================== */
/* This program TODO..... */

// TODO... Add check for personal number format, Add comments

// Function declaration
PERSON input_record(void); // Reads in a person record.
void write_new_file( PERSON *inrecord); // Creates a file and write a first record
void printfile(void); // print out all persons in the file
void search_by_firstname( char *name);// print out person if in list
void append_file(PERSON *inrecord);// appends a new person to the file

void printMenu();
int getUserChoice();
void handleUserChoice(int userChoice);
void createNewFile();
void addNewPersonToFile();
void searchByName();
void searchByLastName(char *name);
char *getUserInput();
void exitProgramme();
void writeToFile(PERSON *inrecord,const char *mode);

int main(void){
    // Variable declarations
    int userChoice = 0;
    while (TRUE) {
        printMenu();
        userChoice = getUserChoice();
        handleUserChoice(userChoice);
    }
}

void printMenu() {
    printf(FIRST_MENU_CHOICE);
    printf(SECOND_MENU_CHOICE);
    printf(THIRD_MENU_CHOICE);
    printf(FOURTH_MENU_CHOICE);
    printf(FIFTH_MENU_CHOICE);
}

int getUserChoice() {
    char input[MAX_LENGTH_USER_INPUT]; // store input
    printf(PROMPT_USER_CHOICE);
    fgets(input,MAX_LENGTH_USER_INPUT, stdin);
    if (input[0] == '\n' || !isdigit(input[0] ) || strlen(input) > 2 ) {
        return FALSE;
    } else {
        char *pointer;
        return (int) strtol(input, &pointer,10);
    }

}
void handleUserChoice(int userChoice) {
    switch (userChoice) {
        case 1:
            createNewFile();
            break;
        case 2:
            addNewPersonToFile();
            break;
        case 3:
            searchByName();
            break;
        case 4:
            printfile();
            break;
        case 5:
            exitProgramme();
            break;
        default:
            printf(PROMPT_INVALID_CHOICE);
            break;
    }
}
void exitProgramme() {
    printf(EXIT_MESSAGE);
    exit(0);
}
void searchByName() {
    int userChoice = 0;
    if(access(FILE_NAME, F_OK )){
        printf(NO_FILE_MESSAGE);
        return;
    }
    printf(PROMPT_SEARCH_TYPE);
    userChoice = getUserChoice();
    if (userChoice == 1) {
        printf(PROMPT_FIRST_NAME);
        search_by_firstname(getUserInput());
    } else if (userChoice == 2) {
        printf(PROMPT_LAST_NAME);
        searchByLastName(getUserInput());
    } else {
        printf(PROMPT_INVALID_CHOICE);
        return;
    }
}

char *getUserInput() {
    char *input; // store input
    input = calloc(MAX_LENGTH_USER_INPUT, sizeof(char));
    if (input == NULL) {
        printf(ERROR_ALLOCATION);
        exitProgramme();
    }
    int keepReading = FALSE;
    do {
        fgets(input,MAX_LENGTH_USER_INPUT, stdin); // read input from buffer and store it in the array
        if (strlen(input) <=2 || input[0] == '\n') {
            keepReading = TRUE;
            printf(PROMPT_INVALID_CHOICE);
            printf(TRY_AGAIN_MESSAGE);
        } else {
            if (input[strlen(input)-1] == '\n' ) {
                input[strlen(input)-1] = '\0';
            }
            keepReading = FALSE;
        }
    } while (keepReading);
    return input;
}

void createNewFile() {
    PERSON dummyPerson = {
            .firstName = "Dummy first name",
            .lastName = "Dummy last name",
            .pers_number = "1234567890123"
    };
    write_new_file(&dummyPerson);
}

void addNewPersonToFile() {
    PERSON person;
    if(access(FILE_NAME, F_OK )){
        printf(NO_FILE_MESSAGE);
    }else{
        person = input_record();
        append_file(&person);
    }
}

PERSON input_record(void) {
    PERSON person;
    char *input;
    printf(PROMPT_FIRST_NAME);
    input = getUserInput();
    strcpy(person.firstName, input);
    free(input);
    printf(PROMPT_LAST_NAME);
    input = getUserInput();
    strcpy(person.lastName, input);
    free(input);
    printf(PROMPT_PERSONAL_NUMBER);
    input = getUserInput();
    // TODO ...
    strcpy(person.pers_number, input);
    free(input);
    return person;
}
void writeToFile(PERSON *inrecord,const char *mode) {
    FILE *file;
    file = fopen(FILE_NAME,mode);
    if (file == NULL) {
        printf(ERROR_OPENING_FILE);
        return;
    }
    fwrite(inrecord,sizeof(PERSON),1,file);
    fclose(file);
};

void append_file(PERSON *inrecord) {
    writeToFile(inrecord, appendToFileMode);
}

void write_new_file(PERSON *inrecord) {
    writeToFile(inrecord, writeToFileMode);
}

void search_by_firstname( char *name) {
    FILE *file;
    int personFound = FALSE;
    int i;
    file = fopen(FILE_NAME, readFromFileMode);
    if (file == NULL) {
        printf(ERROR_OPENING_FILE);
        return;
    }
    PERSON person;
    for(i = 1;;) {
        size_t n = fread(&person, sizeof(PERSON),1, file);
        if (n == 0) {
            break;
        }
        if (strcmp(person.firstName, name) == 0){
            printf(PERSON_FOUND_MESSAGE, i++, person.firstName, person.lastName, person.pers_number);
            personFound = TRUE;
        }
    }
    if (!personFound) {
        printf(PERSON_NOT_FOUND_MESSAGE);
    }
    fclose(file);
    free(name);
}

void searchByLastName( char *name) {
    FILE *file;
    int personFound = FALSE;
    int i;
    file = fopen(FILE_NAME, readFromFileMode);
    if (file == NULL) {
        printf(ERROR_OPENING_FILE);

        return;
    }
    PERSON person;
    for (i = 1;; ) {
        size_t n = fread(&person, sizeof(PERSON), 1, file);
        if (n == 0) {
            break;
        }
        if (strcmp(person.lastName, name) == 0) {
            printf(PERSON_FOUND_MESSAGE, i++, person.firstName, person.lastName, person.pers_number);
            personFound = TRUE;
        }
    }
    if (!personFound) {
        printf(PERSON_NOT_FOUND_MESSAGE);
    }
    fclose(file);
    free(name);
}

void printfile(void) {

    FILE *file;
    int i;
    file = fopen(FILE_NAME, readFromFileMode);
    if (file == NULL) {
        printf(ERROR_OPENING_FILE);
        return;
    }
    PERSON person;
    for(i = 1;;i++) {
        size_t n = fread(&person, sizeof(PERSON),1, file);
        if (n == 0) {
            break;
        }
        if (i == 1) {
            printf(PRINT_DUMMY_RECORD, person.firstName, person.lastName, person.pers_number);
        } else {
            printf(PRINT_PERSON_DATA, person.firstName, person.lastName, person.pers_number);
        }

    }
    fclose(file);

}