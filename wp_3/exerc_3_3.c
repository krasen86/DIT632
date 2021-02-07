#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//#### Constants #####
#define MAX 5

// ##### Typedefs ###
typedef struct q{
    int number;
    struct q *next;
    struct q *prev;
} REGTYPE;

// ##### Funcion declarations #####
REGTYPE* random_list(void);
REGTYPE* add_first(REGTYPE* temp, int data);

//###### Main program #######
int main(int argc, char *argv[]){
    int nr = 0;
    REGTYPE *akt_post, *head=NULL;
    srand(time(0));  //Random seed
    head=random_list();
    akt_post=head;

    while(akt_post != NULL){
        printf("\n Post nr %d : %d" , nr++, akt_post->number);
        akt_post = akt_post -> next;
    }

    // --- Free of allocated memory  ---
    while((akt_post = head) != NULL){
        head=akt_post->next;
        free(akt_post);
    }
    return 0;
}

// ====     End of main   =====================================

REGTYPE* random_list(void){
    int nr, i;
    REGTYPE *top, *old, *item;
    item = (struct q*)malloc(sizeof(struct q));

    printf("hey");

    for (i = 0; i < MAX; i++){
        nr = rand() % 100;
        if(top == NULL){
            item -> prev = NULL;
            item -> next = NULL;
            item -> number = nr;
            top = item;
        } else {
            item -> number = nr;
            item -> prev = NULL;
            item -> next = top;
            top -> prev = item;
            top = item;
        }
    }
    return(top);
}

REGTYPE* add_first(REGTYPE* temp, int data){

}// Adds a record first i list and set the field tal to data