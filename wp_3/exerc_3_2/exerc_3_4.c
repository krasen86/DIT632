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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Define section
#define LENGTH_NAME 20
#define LENGTH_PERSONAL_NUMBER 13 // yyyymmddnnnc
#define TRUE 1
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




int main( void){
    // Variable declarations
    PERSON *person;
    person = malloc(sizeof(PERSON));
    strcpy(person -> firstName, "Krasen");
    strcpy(person -> lastName, "Parvanov");
    strcpy(person -> pers_number, "New");
    write_new_file(person);
    strcpy(person -> firstName, "John");
    strcpy(person -> lastName, "John");
    strcpy(person -> pers_number, "New");
    append_file(person);
    printfile();
    char name[7] = {"Roy"};
    search_by_firstname(name);
    return(0);
}
void append_file(PERSON *inrecord) {
    FILE *file;
    file = fopen("person.bin","a");
    if (file == NULL) {
        printf("Error\n");
        return;
    }
    fwrite(inrecord,sizeof(PERSON),1,file);
    printf("Append\n");
    fclose(file);
}
void write_new_file(PERSON *inrecord) {
    FILE *file;
    file = fopen("person.bin","wb");
    if (file == NULL) {
        printf("Error\n");
        return;
    }
    fwrite(inrecord,sizeof(PERSON),1,file);
    printf("Wrote\n");
    fclose(file);
}
void search_by_firstname( char *name) {
    FILE *file;
    int personFound = 0;
    int i;
    file = fopen("person.bin","rb");
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
    fclose(file);
}

void printfile(void) {

    FILE *file;
    file = fopen("person.bin","rb");
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