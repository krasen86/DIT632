/* ====================================
File name: exerc_1_3.c (or cpp)
Date: 2020-01-26
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 4783
====================================== */

// Include section
#include "stdio.h"

// Define section
#define INPUT_PROMPT "Please enter a string you want encrypted\n" // Prompt user for a string
#define ENCRYPTED_NOTIFICATION "Encrypted string: %s \n" // Template to print the encrypted string
#define SIZE_OF_LINE 100 // Maximum allowed characters for user input
#define ENCRYPTION_VALUE 13 // Integer to be added/subtracted to/from the ASCII value in order to encrypt the string
#define FIRST_LOWERCASE_ASCII 97 // ASCII value for the first lower case character in the alphabet ('a')
#define LOWER_CASE_ADDITION_ASCII 109 // ASCII value for char 'm' which is the 'break point' of specifying the second half
                                      // of the alphabet in lowercase
#define UPPER_CASE_ADDITION_ASCII 77 // ASCII value for char 'm' which is the 'break point' of specifying the second half
                                     // of the alphabet in uppercase
#define EXIT_MESSAGE "Thank you for using our encryption application! Bye!\n" // String to be printed when program is terminated

/* ==================================== Main program section ====================================== */
/* Simple encryption algorithm that given an input string from the user encrypts it following the
 * "shifts of characters" principal in the ASCII-code table and prints the result to the user. */

int main() {
    // Variable declarations
    char input[SIZE_OF_LINE]; // Store user input into character array
    int i; // Variable used for iterating through the input character array

    do {
        i = 0; // Assign 0 to the variable that iterates through the array
        printf(INPUT_PROMPT); // Prompt user for input
        fgets(input, sizeof(input), stdin); // Read user input from buffer and store into character array
        // Loop to iterate over the input characters string stored in character array

        while (input[i] != '\0') {                                // Using the null character to control the condition of the loop
            if (input[i] >= FIRST_LOWERCASE_ASCII) {              // Check if the character is a lowercase
                if (input[i] <= LOWER_CASE_ADDITION_ASCII) {      // Check if the specific character belongs to the first half of the lowercase alphabet
                    input[i] += ENCRYPTION_VALUE;                 // Encrypt the character by incrementing its ASCII value by the encryption value
                } else {                                          // The character belongs to the second half of the lowercase alphabet
                    input[i] -= ENCRYPTION_VALUE;                 // Encrypt the character by decrementing its ASCII value by the encryption value
                }
            } else {                                              // The character is an uppercase
                if (input[i] <= UPPER_CASE_ADDITION_ASCII) {      // Check if the specific character belongs to the first half of the uppercase alphabet
                    input[i] += ENCRYPTION_VALUE;                 // Encrypt the character by incrementing its ASCII value by the encryption value
                } else {                                          // The character belongs to the second half of the uppercase alphabet
                    input[i] -= ENCRYPTION_VALUE;                 // Encrypt the character by decrementing its ASCII value by the encryption value
                }
            }
            i++;  // increment the index
        }
        // Check if the EOF was read from the buffer
        if (!feof(stdin)) {
            printf(ENCRYPTED_NOTIFICATION, input); // print encrypted string whenever the input was not the EOF
        } else {
            printf(EXIT_MESSAGE); // print exit message to the user
        }
    } while(!feof(stdin)); // iterate until EOF is read from buffer

    return 0; // Exit the program
}