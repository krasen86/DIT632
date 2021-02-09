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

// ##### Function declarations #####
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

    head = add_first(head, 10);
    akt_post = head;
    nr = 0;
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
    REGTYPE *top = NULL, *old, *item;

    for (i = 0; i < MAX; i++){
        item = (struct q*)malloc(sizeof(struct q));
        nr = rand() % 100;
        item -> number = nr;
        if(top == NULL){
            item -> prev = NULL;
            item -> next = NULL;
            top = item;
        } else {
            old = top;
            while(old->next!=NULL){
                old = old->next;
            }
            old -> next = item;
            item -> prev = old;
            item -> next = NULL;
        }
    }
    return(top);
}

REGTYPE* add_first(REGTYPE* temp, int data){
    REGTYPE *item;
    item = (struct q*)malloc(sizeof(struct q));

    if(temp == NULL) {
        temp -> number = data;
        temp -> next = NULL;
        temp -> prev = NULL;
    }else {
        item -> number = data;
        item -> next = temp;
        item -> prev = NULL;
        temp = item;
    }
    return temp;
}// Adds a record first i list and set the field tal to data