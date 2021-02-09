// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Constants
#define MAX 5   // Define variable for length of the linked list
#define ADD_FIRST_NUMBER 10 // Define variable to be used to push to the front of the linked list
#define PRINT_POST "Post nr %d : %d \n" // String used to print the linked list values
#define FIRST_ITERATION_STRING "Random numbers added to linked list\n" // String to be printed after generating a linked list with random numbers
#define SECOND_ITERATION_STRING "Add %d to start of linked list\n"  // String to be printed when printing linked list after a number has been pushed to the front

//Typedefs
typedef struct q{
    int number;
    struct q *next;
    struct q *prev;
} REGTYPE;

//Function declarations
REGTYPE* randomList(); // Function to create a doubly linked list with length MAX using random numbers 0-100
REGTYPE* addFirst(REGTYPE* temp, int data); // Function to add a ADD_FIRST_NUMBER to the linked list
void printList(REGTYPE* head);  // Function to print linked list


//Main program
int main(){
    // Variable declarations
    REGTYPE *post, *head=NULL;      // Declare post to be able to iterate through linked list,
                                    // Initialize head to null
    srand(time(0));     // Random seed

    head = randomList();    // Set head to the randomly generated linked list's head
    post = head;            // Set post to the current head
    printf(FIRST_ITERATION_STRING); // Print string for the first iteration print
    printList(post);                // Print the linked list

    head = addFirst(head, ADD_FIRST_NUMBER);    // Set head to the new head by calling method to push a number to the front of the list
    post = head;                                // Set post to current head
    printf(SECOND_ITERATION_STRING, ADD_FIRST_NUMBER);            // Print string for the second iteration print
    printList(post);                            // Print the linked list

    // --- Free of allocated memory  ---
    while((post = head) != NULL){
        head=post->next;
        free(post);
    }

    return 0;
}

//End of main


REGTYPE* randomList(){
    // Variable declarations
    int randomNumber, i; // Declare randomNumber to be used to generate randomnumbers for, Declare i to iterate in for loop
    REGTYPE *top = NULL, *old, *item; // Initialize top to NULL for first iteration, declare old as a temp variable and item as the new struct to be pushed into the linked list

    for (i = 0; i < MAX; i++){ // For loop to iterate MAX amount of numbers into the linked list
        item = (struct q*)malloc(sizeof(struct q)); // Allocate memory for a new struct item
        randomNumber = rand() % 100; // Generate a random number between 0-100
        item -> number = randomNumber;  // Set number of item to the random number
        if(top == NULL){         // Check if top is null
            item -> prev = NULL; // Set prev to default NULL when top is empty
            item -> next = NULL; // Set next to default NULL when top is empty
            top = item;          // Set top to item since it's the first item in the list
        } else {                 // If top is not empty
            old = top;           // Se the variable old to the current head(top)
            while(old->next!=NULL){ // Iterate until we find the end of the linked list
                old = old->next;    // Set old to old->next to iterate through the list
            }
            old -> next = item;     // Set the last item in the linked list to point to the newly generated item
            item -> prev = old;     // Set the newly generated item in the list to point to the old end of the linked list
            item -> next = NULL;    // Set item-> next to null since it's the last item in the linked list
        }
    }
    return(top);    // Return the head of the linked list
}

REGTYPE* addFirst(REGTYPE* temp, int data){
    //Variable declarations
    REGTYPE *item;  // Variable to be used to push to front of the linked list
    item = (struct q*)malloc(sizeof(struct q)); // Allocate memory for the item

    if(temp == NULL) { // Check if temp(head) is null
        temp -> number = data; // Set the head to the new data, since the list is empty
        temp -> next = NULL;   // set next to null, default value, since the list is empty
        temp -> prev = NULL;   // set prev to null, default value, since the list is empty
    }else {
        item -> number = data; // Set the new items number to data
        item -> next = temp; // Set items next to point to the current head of the linked list
        item -> prev = NULL; // Set items prev to point to null, since it's the first item in the list
        temp = item; // Set a new head, since we pushed to the front of the list
    }
    return temp; // Return the head of the list
}// Adds a record first i list and set the field tal to data

void printList(REGTYPE* post) {
    //Variable declarations
    int i = 0; // variable to be used to print the current post number
    while(post != NULL){ // Loop until the end of the list
        printf(PRINT_POST, i++, post->number); // Print the data of the current spot in the list
        post = post -> next; // Iterate forward in the linked list by setting post to the next place of the list
    }
}