#include "stdio.h"

#define INPUT_PROMP "Please enter a string you want encrypted\n"
#define ENCRYPTED_NOTIFICATION "Encrypted string: %s \n"
#define SIZE_OF_LINE 256
#define ENCRYPTION_VALUE 13
#define LOWER_CASE_ASCII 96
#define LOWER_CASE_ADDITION_ASCII 109
#define UPPER_CASE_ADDITION_ASCII 77

int main() {

    char input[SIZE_OF_LINE];

    do {
        int i = 0;
        printf(INPUT_PROMP);
        fgets(input, sizeof(input), stdin);
        while (input[i] != '\0') {
            if (input[i] > LOWER_CASE_ASCII) {
                if (input[i] <= LOWER_CASE_ADDITION_ASCII) {
                    input[i] += ENCRYPTION_VALUE;
                } else {
                    input[i] -= ENCRYPTION_VALUE;
                }
            } else {
                if (input[i] <= UPPER_CASE_ADDITION_ASCII) {
                    input[i] += ENCRYPTION_VALUE;
                } else {
                    input[i] -= ENCRYPTION_VALUE;
                }
            }
            i++;
        }
        printf(ENCRYPTED_NOTIFICATION, input);
    } while(!feof(stdin));
}