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
#include "personalNumberValidator.h" // include the custom library needed for checking the personal number's validity

// Define section
#define LENGTH_NAME 20 // Maximum allowed characters for the names
#define LENGTH_PERSONAL_NUMBER 13 // yyyymmddnnnc
#define TRUE 1      // Define true
#define FALSE 0     // Define false
#define FILE_NAME "person.bin" // specify the file name
#define FIRST_MENU_CHOICE "\n\t1 Create a new and delete the old file.\n" // String to be printed as the first option in the menu
#define SECOND_MENU_CHOICE "\t2 Add a new person to the file.\n" // String to be printed as the second option in the menu
#define THIRD_MENU_CHOICE "\t3 Search for a person in the file.\n" // String to be printed as the third option in the menu
#define FOURTH_MENU_CHOICE "\t4 Print out all in the file.\n" // String to be printed as the fourth option in the menu
#define FIFTH_MENU_CHOICE "\t5 Exit the program.\n" // String to be printed as the fifth option in the menu
#define PROMPT_USER_CHOICE "Enter your choice: " // String to be printed to prompt user
#define MAX_LENGTH_USER_INPUT 100 // accepted size of user input
#define PROMPT_SEARCH_TYPE "Press 1 to search by first name OR Press 2 to search by last name\n" // Prompt the user to choose an option to search by either specifying the first name or the last name
#define PROMPT_INVALID_CHOICE "That was not a valid input.....\n" // Notify the user for invalid input
#define TRY_AGAIN_MESSAGE "Try again: " // String to be printed to prompt for the user's input
#define PROMPT_FIRST_NAME "Please enter first name: " // String to be printed for the user to enter the first name
#define PROMPT_LAST_NAME "Please enter last name: " // String to be printed for the user to enter the last name
#define EXIT_MESSAGE "\nThank you for using the application!\n" //  Exit message to be printed
#define PRINT_PERSON_DATA "Person: \n\tFirst Name: \t\t%s\n\tLast name: \t\t\t%s\n\tPersonal number: \t%s\n\n" // Print the person's information
#define PRINT_DUMMY_RECORD "Dummy record: \n\tFirst Name: \t\t%s\n\tLast name: \t\t\t%s\n\tPersonal number: \t%s\n\n" // Print dummy information when file was created
#define ERROR_OPENING_FILE "Error opening the file and/or file doesn't exists...\n" // String to be printed when there is an error while trying to open the file
#define PERSON_NOT_FOUND_MESSAGE "Person with that name was not found.\n" // String to be printed when the search does not find any results
#define PERSON_FOUND_MESSAGE "Result %d\nPerson found:\n\tFirst Name: \t\t%s\n\tLast name: \t\t\t%s\n\tPersonal number: \t%s\n\n" // String used to display the results after finding a person
#define PROMPT_PERSONAL_NUMBER "Please enter your personal number in format <yyyymmddnnnc>: " // Prompt user to enter their personal number
#define ERROR_ALLOCATION "Memory allocation failed. Please try again\n" // Notify the user for memory allocation failure
#define NO_FILE_MESSAGE "There is currently no file. Please create a file first...\n" // String to be printed when there is no file created
#define INVALID_PERSONAL_NUMBER_MESSAGE "You entered an invalid personal number.\n" // String to be printed when an invalid personal number was received
#define ERROR_CODE_FILE_NOT_FOUND -1 // Error code when the file could not be accessed
#define SUCCESSFUL_PERSON_WRITE "\nThe following entry has been successfully written to the file:\n\tFirst Name: \t\t%s\n\tLast name: \t\t\t%s\n\tPersonal number: \t%s\n\n"
#define SELECT_MENU_OPTION "Please type a number based on your choice from the list below:"
// -----Typedefs -------
// Structure defining a person with a first name, last name and a personal number
typedef struct {
    char firstName[LENGTH_NAME];
    char lastName[LENGTH_NAME];
    char personalNumber[LENGTH_PERSONAL_NUMBER];
}PERSON;

// Constants declaration
const char appendToFileMode[] = "ab"; // defines the append binary mode when opening a file
const char readFromFileMode[] = "rb"; // defines the read binary mode when opening a file
const char writeToFileMode[] = "wb"; // defines the write binary mode when opening a file

/* ==================================== Main program section ====================================== */
/* This is an implementation of a program used to manage a database of people that is saved as a binary
 * file. The user has the option to create a file (and delete the old one), add a new person entry into
 * the database by providing first name, last name and a personal number, which is validated with the use
 * of the custom library that is being provided. Also, the user can search for a person, as well as print
 * the contents of the file, with all of its entries.
 */

// Function declaration
PERSON inputRecord(void); // Reads in a person record.
void printFile(void); // print out all persons in the file
void searchByFirstName(char *name);// print out person if in list
void printMenu(); // Display the main menu
int getUserChoice(); // Read the user's choice for the menu options
void handleUserChoice(int userChoice); // Process the selected option from the menu
void createNewFile(); // Create a new file and write the dummy entry
void addNewPersonToFile(); // Process the addition of a new person entry to the file
void searchByName(); // Display the sub-menu selection for search options by name
void searchByLastName(char *name); // Search for a person by their last name
char *getUserInput(); // Read the user's input
void exitProgramme(); // Exit the program
void writeToFile(PERSON *person, const char *mode); // Write the entry into the file based on the specified mode
char *readPersonalNumber(); // Read the user's personal number

int main(void){
    // Variable declarations
    int userChoice; // Store the user's selection for the menu

    // Main loop
    while (TRUE) {
        printMenu(); // print the main menu
        userChoice = getUserChoice(); // Read the user's choice for the menu and store it to the userChoice variable
        handleUserChoice(userChoice); // Process the selection based on the user's choice
    }
}

// Function to print the main selection menu
void printMenu() {
    printf(SELECT_MENU_OPTION);
    printf(FIRST_MENU_CHOICE); // print the first menu option
    printf(SECOND_MENU_CHOICE); // print the second menu option
    printf(THIRD_MENU_CHOICE); // print the third menu option
    printf(FOURTH_MENU_CHOICE); // print the fourth menu option
    printf(FIFTH_MENU_CHOICE); // print the fifth menu option
}

// Function that reads the user's choice for the menu options
int getUserChoice() {
    char input[MAX_LENGTH_USER_INPUT]; // store input
    printf(PROMPT_USER_CHOICE); // prompt the user to enter an option
    fgets(input,MAX_LENGTH_USER_INPUT, stdin);

    if (input[0] == '\n' || !isdigit(input[0] ) || strlen(input) > 2 ) { // check if there was an empty line provided or not a number or the length higher than 1 digit
        return FALSE; // return 0
    } else { // case of valid choice
        char *pointer; // define a pointer needed for the strtol() conversion from character type to long
        return (int) strtol(input, &pointer,10); // Return the casted value return by strtol function
    }

}

// Function to process the selected menu option
void handleUserChoice(int userChoice) {
    switch (userChoice) { // define a switch statement for all possible menu options
        case 1: // case of creating a new file
            createNewFile(); // call the function to create a new file
            break;
        case 2: // case of adding a new person to the file
            addNewPersonToFile(); // call the function to add the new person
            break;
        case 3: // case of searching for a person in the file
            searchByName(); // call the function to search for a person
            break;
        case 4: // case of printing the entries in the file
            printFile(); // call the function to print the file's entries
            break;
        case 5: // case for exiting the program
            exitProgramme(); // call the function to exit the program
            break;
        default: // default case for invalid input
            printf(PROMPT_INVALID_CHOICE); // print an invalid input message to the user
            break;
    }
}

// Function to terminate the program
void exitProgramme() {
    printf(EXIT_MESSAGE);
    exit(0);
}

// Function to search for a person by name
void searchByName() {
    int userChoice; // store the user's selection
    if(access(FILE_NAME, F_OK ) == ERROR_CODE_FILE_NOT_FOUND){ // check if the file does not exist
        printf(NO_FILE_MESSAGE); // print notification for the file not existing
        return; // return since the search cannot be performed without a file
    }

    printf(PROMPT_SEARCH_TYPE); // prompt the user to search by either first or last name
    userChoice = getUserChoice(); // get the user's choice
    if (userChoice == 1) { // check if the user wants to search by first name
        printf(PROMPT_FIRST_NAME); // prompt the user to enter a first name
        searchByFirstName(getUserInput()); // call the function to search by first name by first reading the user's input
    } else if (userChoice == 2) { // check if the user wants to search by last name
        printf(PROMPT_LAST_NAME); // prompt the user to enter a last name
        searchByLastName(getUserInput()); // call the function to search by last name by first reading the user's input
    } else { // invalid option
        printf(PROMPT_INVALID_CHOICE); // notifying the user for an invalid option
        return; // return since you can't perform a search without providing a valid option
    }
}

// Function to read the user's input
char *getUserInput() {
    char *input; // store input
    int keepReading = FALSE; // boolean to control the loop
    input = calloc(MAX_LENGTH_USER_INPUT, sizeof(char)); // allocate memory for the user's input and initialize it

    if (input == NULL) { // check if the allocation failed
        printf(ERROR_ALLOCATION); // notify the user for an allocation error
        exitProgramme(); // exit the program
    }

    do {
        fgets(input,MAX_LENGTH_USER_INPUT, stdin); // read input from buffer and store it in the array
        if (strlen(input) <=2 || input[0] == '\n') { // check if there was an empty line provided or the length higher than 1 digit
            keepReading = TRUE; // continue the loop when entered an invalid input
            printf(PROMPT_INVALID_CHOICE); // notify the user for invalid choice
            printf(TRY_AGAIN_MESSAGE); // prompt the user to try again
        } else { // is valid input
            if (input[strlen(input)-1] == '\n' ) {  // check and alter the last character for a valid input
                input[strlen(input)-1] = '\0';      // from the "enter" character to the end of string
            }
            keepReading = FALSE; // break the loop
        }
    } while (keepReading); // iterate while not valid input has been provided
    return input; // return the input
}

//Function to create the dummy entry to the file
void createNewFile() {
    // create a dummy person structure
    PERSON dummyPerson = {
            .firstName = "Dummy first name",
            .lastName = "Dummy last name",
            .personalNumber = "1234567890123"
    };
    writeToFile(&dummyPerson, writeToFileMode); // write the dummy person entry to the file
}

// Function to add a new person entry to the file
void addNewPersonToFile() {
    PERSON person; // store the entry for the person
    if(access(FILE_NAME, F_OK ) == ERROR_CODE_FILE_NOT_FOUND){ // check if the file does not exist
        printf(NO_FILE_MESSAGE); // notify the user if the file does not exist
        return;
    }else{ // if the file exists
        person = inputRecord(); // call the function to initialize the person to be added to the file
        writeToFile(&person, appendToFileMode); // call the function to add the person to the file
    }
}

// Function that returns an initialized record of a person
PERSON inputRecord(void) {
    PERSON person; // store the entry for the person
    char *input; // store the input to a pointer

    printf(PROMPT_FIRST_NAME); // prompt the user for a first name
    input = getUserInput(); // call the function to read the user's input and store it
    strcpy(person.firstName, input); // copy the value to the structure
    free(input); // free the pointer's memory

    printf(PROMPT_LAST_NAME); // prompt the user for a last name
    input = getUserInput(); // call the function to read the user's input and store it
    strcpy(person.lastName, input); // copy the value to the structure
    free(input); // free the pointer's memory

    printf(PROMPT_PERSONAL_NUMBER);// prompt the user for a personal number
    input = readPersonalNumber(); // call the function to read the user's input and store it
    strcpy(person.personalNumber, input); // copy the value to the structure
    free(input); // free the pointer's memory

    return person; // return the initialized entry
}

// Function that handles the reading and the validation of the personal number
char *readPersonalNumber() {
    char *input; // pointer to store the input
    int validInput; // boolean to control the loop

    do {
        input = getUserInput(); // read user input and assign its value
        validInput = validatePersonalNumber(input); // call function to valid the entered personal number and assign to a control variable
        if (!validInput) { // if the personal number is not valid
            printf(INVALID_PERSONAL_NUMBER_MESSAGE); // notify the user for an invalid personal number
            printf(TRY_AGAIN_MESSAGE); // prompt the user to enter another personal number
        }
    } while (!validInput); // iterate as long as the provided personal number is incorrect

    return input; // return the personal number
}

// Function to write a person to a file by specifying the opening file mode
void writeToFile(PERSON *person, const char *mode) {
    FILE *file; // stores the pointer for the file
    file = fopen(FILE_NAME,mode); // open file based on the specified mode and name
    if (file == NULL) { // check if the file opening failed
        printf(ERROR_OPENING_FILE); // notify the user for an opening file failure
        return;
    }

    fwrite(person, sizeof(PERSON), 1, file); // write one entry for the provided person based on the size of the structure
    printf(SUCCESSFUL_PERSON_WRITE, person->firstName, person->lastName, person->personalNumber); // print a successful message when writing to the file

    fclose(file); // close the file
}

// Function to search for a person by first name
void searchByFirstName(char *name) {
    FILE *file; // stores the pointer for the file
    int personFound = FALSE; // boolean to keep track whether a person was found or not
    int i = 1; // index for counting the number of entries found
    file = fopen(FILE_NAME, readFromFileMode); // open file based on the readFromFileMode and name
    if (file == NULL) { // check if the opening of the file failed
        printf(ERROR_OPENING_FILE); // notify the user for an opening file failure
        return;
    }
    PERSON person; // store the entry for the person
    while (TRUE) {
        size_t n = fread(&person, sizeof(PERSON),1, file); // read one entry from the file based on the size of PERSON structure and store how many records have been read successfully in n
        if (n == 0) { // if no records have been read
            break; // break the loop
        }
        if (strcmp(person.firstName, name) == 0){ // check if the first name of the read entry is equal to the provided first name
            printf(PERSON_FOUND_MESSAGE, i++, person.firstName, person.lastName, person.personalNumber); // display the entry
            personFound = TRUE; // set the boolean to ture
        }
    }
    if (!personFound) { // if there was not person found
        printf(PERSON_NOT_FOUND_MESSAGE); // notify the user for not finding any person
    }
    fclose(file); // close the file
    free(name); // free the memory for the pointer
}

// Function to search for a person by last name
void searchByLastName(char *name) {
    FILE *file; // stores the pointer for the file
    int personFound = FALSE; // boolean to keep track whether a person was found or not
    int i = 1; // index for counting the number of entries found
    file = fopen(FILE_NAME, readFromFileMode); // open file based on the readFromFileMode and name
    if (file == NULL) { // check if the opening of the file failed
        printf(ERROR_OPENING_FILE); // notify the user for an opening file failure
        return;
    }
    PERSON person; // store the entry for the person
    while (TRUE) {
        size_t n = fread(&person, sizeof(PERSON),1, file); // read one entry from the file based on the size of PERSON structure and store how many records have been read successfully in n
        if (n == 0) { // if no records have been read
            break; // break the loop
        }
        if (strcmp(person.lastName, name) == 0){ // check if the last name of the read entry is equal to the provided last name
            printf(PERSON_FOUND_MESSAGE, i++, person.firstName, person.lastName, person.personalNumber); // display the entry
            personFound = TRUE; // set the boolean to ture
        }
    }
    if (!personFound) { // if there was not person found
        printf(PERSON_NOT_FOUND_MESSAGE); // notify the user for not finding any person
    }
    fclose(file); // close the file
    free(name); // free the memory for the pointer
}

// Function to print all the entries in the file
void printFile(void) {

    FILE *file; // stores the pointer for the file
    int i; // index for the loop
    file = fopen(FILE_NAME, readFromFileMode); // open file based on the readFromFileMode and name
    if (file == NULL) {  // check if the file opening failed
        printf(ERROR_OPENING_FILE); // notify the user for an opening file failure
        return;
    }
    PERSON person; // store the entry for the person
    for(i = 1;;i++) { // start the iteration loop
        size_t n = fread(&person, sizeof(PERSON),1, file); // read one entry from the file based on the size of PERSON structure and store how many records have been read successfully in n
        if (n == 0) { // if no records have been read
            break; // break the loop
        }
        if (i == 1) { // check if it's the first entry
            printf(PRINT_DUMMY_RECORD, person.firstName, person.lastName, person.personalNumber); // print the dummy person
        } else { // for the other entries
            printf(PRINT_PERSON_DATA, person.firstName, person.lastName, person.personalNumber); // print the person
        }

    }
    fclose(file); // close the file

}