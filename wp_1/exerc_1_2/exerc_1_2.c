#include "stdio.h"
#include "string.h"

#define MAX 500
#define False 0
#define True 1

int main() {

    char inputLine[MAX];
    int count = 0, i;
    int foundLetter = False;

    printf("Enter a sentence\n");
    fgets(inputLine, MAX, stdin);
    
    for (i = 0; i < strlen(inputLine); i++)
    {
        if (inputLine[i] == ' ' || inputLine[i] == '\n')
            foundLetter = False;
        else 
        {    
            if (foundLetter == False)
                count++;
            foundLetter = True;
        }
    }

    printf("Total number of words in the sentence is: %d\n", count);
    return 0;

}