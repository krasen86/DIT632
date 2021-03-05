#include "person.h"

//typedef struct Person{
//    char personFirstName[MAX]; // person's given Name
//    char personLastName[MAX]; // person's family Name
//    char personalNumber[MAX]; // person's personalNumber
//    char personAddress[MAX]; // person's address
//    int personAge; // person's age
//} Person;
//
//typedef struct List {
//    struct Person person;
//    struct List *next;
//} List;

//void insertPerson(struct Person person);
//void printList();
//int getNumberOfPersons();
//struct Person* getAll();



void insertPerson(struct Person person){
    List *node, *temp;
    node = (struct List*)malloc(sizeof(struct List));
    node -> person = person;
    node -> next = NULL;
    if(head == NULL){
        head = node;
    }else{
        temp = head;
        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = node;
    }
}
int getNumberOfPersons(){
    List *temp = head;
    int i = 0;
    if(temp == NULL){
        return i;
    }else{
        while(temp != NULL){
            i++;
            temp = temp -> next;
        }
        return i;
    }
}
