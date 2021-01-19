#include "stdio.h"

#define SENTENCE_ONE   "You selected 1 \n"
#define SENTENCE_TWO   "You selected 2 \n"
#define SENTENCE_THREE "You selected 3 \n"
#define SENTENCE_FOUR  "You selected 4 \n"
#define SENTENCE_FIVE  "You selected 5 \n"
#define SENTENCE_WRONG_INPUT "Not a valid input \n"


int main() {

    int selectedOption;
    do
    {
       printf("Please enter a number between 1 and 5.\n");
       selectedOption = getchar();
       if (selectedOption == EOF ) 
       {
           printf(SENTENCE_WRONG_INPUT);
           return 0;
       } 
       switch (selectedOption)
       {
       case '1':
           printf(SENTENCE_ONE);
           break;
        case '2':
           printf(SENTENCE_TWO);
           break;
        case '3':
           printf(SENTENCE_THREE);
           break;
        case '4':
           printf(SENTENCE_FOUR);
           break;
        case '5':
           printf(SENTENCE_FIVE);
           break;
       default:
            printf(SENTENCE_WRONG_INPUT);
           break;
       }  
    } while (selectedOption > '0' && selectedOption < '6');
    return 0;
}