#include "stdio.h"
#include "string.h"

#define INPUT_PROMP "Enter a sentence\n"
#define WORD_COUNT_NOTIFICATION "Total number of words in the sentence is: %d\n"
#define MAX_CHARECTERS 500
#define FALSE 0
#define TRUE 1

int main() {

    char inputSentence[MAX_CHARECTERS];
    int wordCount = 0;
    int i;
    int foundLetter = FALSE;

    printf(INPUT_PROMP);
    fgets(inputSentence, MAX_CHARECTERS, stdin);
    
    for (i = 0; i < strlen(inputSentence); i++)
    {
        if (inputSentence[i] == ' ' || inputSentence[i] == '\n') {
            foundLetter = FALSE;
        }     
        else 
        {    
            if (foundLetter == FALSE) {
                wordCount++;
            }   
            foundLetter = TRUE;
        }
    }

    printf(WORD_COUNT_NOTIFICATION, wordCount);
    return 0;

}