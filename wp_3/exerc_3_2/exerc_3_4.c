/*File managements of a person register
You should write a program for manage a database of people. The database should be stored to the
hard disc as a binary file. The function of the program is easiest to understand by reading the
description and program skeleton below.
From the main program you should be able to choose between these options:
1 Create a new and delete the old file.
2 Add a new person to the file.
3 Search for a person in the file .
4 Print out all in the file.
5 Exit the program.
After entered the choice the program executes the task and returns to the menu for new choices.
1. Create a new and delete the old file.
Program creates a new file with the specified filename (fixed) and writes a first dummy record to
the file and then close it.
2. Add a new person to the file.
First gives an opportunity to put in one new person to a temp record and then add this record in
the end of the file.
3. Search for a person in the file.
Gives you an opportunity to search for all persons with either a specified first name or
family name ( by choice).The program prints out all person with that name.
4. Print out all in file.
Prints out the whole list
 5. Exit the program.
Just exits the program.
 */
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
#define PROMPT_SEARCH_TYPE "Press 1 to search by first name OR Press 2 to search by last name\nEnter here: "
#define PROMPT_INVALID_CHOICE "That was not a valid input.....\n"
#define PROMPT_FIRST_NAME "Please enter first name: "
#define PROMPT_LAST_NAME "Please enter last name: "


// -----Typedefs -------
typedef struct {
    char firstName[LENGTH_NAME];
    char lastName[LENGTH_NAME];
    char pers_number[LENGTH_PERSONAL_NUMBER];
}PERSON;

/* ==================================== Main program section ====================================== */
/* This program TODO..... */



// Function declaration
PERSON input_record(void); // Reads in a person record.
void write_new_file( PERSON *inrecord); //Creats a file and write a first record
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


int main(void){
    // Variable declarations
    int userChoice = 0;
    while (TRUE) {
        printMenu();
        userChoice = getUserChoice();
        handleUserChoice(userChoice);
    }

    printfile();
    char name[7] = {"Roy"};
    printf("Please enter a namen to search: ");
    char input[100]; // store input
    search_by_firstname(fgets(input,100, stdin));
    return(0);
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
    if (input[0] == '\n' || !isdigit(input[0] || strlen(input) > 2) ) {
        return 0;
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

            break;
        default:
            break;
    }
}

void searchByName() {
    int userChoice = 0;
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
    int keepReading = FALSE;
    do {
        fgets(input,MAX_LENGTH_USER_INPUT, stdin); // read input from buffer and store it in the array
        if (strlen(input) <=2 || input[0] == '\n') {
            keepReading = TRUE;
            printf(PROMPT_INVALID_CHOICE);
        } else {
            keepReading = FALSE;
        }
    } while (keepReading);
    return input;
}

void createNewFile() {
    PERSON dummyPerson = {
            .firstName = "Test first name",
            .lastName = "Test last name",
            .pers_number = "1234567890123"
    };
    write_new_file(&dummyPerson);
}

void addNewPersonToFile() {
    PERSON person;
    person = input_record();
    append_file(&person);
}

PERSON input_record(void) {
    PERSON person;
    char input[100]; // store input
    printf("Please enter your first name: ");
    fgets(input,100, stdin); // read input from buffer and store it in the array
    strcpy(person.firstName, input);
    printf("Please enter your last name: ");
    fgets(input,100, stdin); // read input from buffer and store it in the array
    strcpy(person.lastName, input);
    printf("Please enter your personal number (yyyymmddnnnn): ");
    fgets(input,100, stdin); // read input from buffer and store it in the array
    strcpy(person.pers_number, input);
    return person;
}

void append_file(PERSON *inrecord) {
    FILE *file;
    file = fopen(FILE_NAME,"ab");
    if (file == NULL) {
        printf("Error\n");
        return;
    }
    fwrite(inrecord,sizeof(PERSON),1,file);
    printf("Append\n"); // TODO remove
    free(inrecord);
    fclose(file);
}

void write_new_file(PERSON *inrecord) {
    FILE *file;
    file = fopen(FILE_NAME,"wb");
    if (file == NULL) {
        printf("Error\n");
        return;
    }
    fwrite(inrecord,sizeof(PERSON),1,file);
    printf("Wrote\n"); // TODO remove
    free(inrecord);
    fclose(file);
}

void search_by_firstname( char *name) {
    FILE *file;
    int personFound = FALSE;
    int i;
    file = fopen(FILE_NAME,"rb");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }
    PERSON person;
    for(i = 1;;) {
        size_t n = fread(&person, sizeof(PERSON),1, file);
        if (n == 0) {
            break;
        }
        if (strcmp(person.firstName, name) == 0){
            printf("Result %d\nPerson found: %s, %s, %s\n", i, person.firstName, person.lastName, person.pers_number);
            personFound = TRUE;
        }
    }
    if (!personFound) {
        printf("Person with that name was not found.\n");
    }
    free(name);
    fclose(file);
}

void printfile(void) {

    FILE *file;
    file = fopen(FILE_NAME,"rb");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }
    PERSON person;
    while(TRUE) {
        size_t n = fread(&person, sizeof(PERSON),1, file);
        if (n == 0) {
            break;
        }
        printf("Person: %s, %s, %s\n", person.firstName, person.lastName, person.pers_number);
    }
    fclose(file);

}