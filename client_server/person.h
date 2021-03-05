#ifndef DIT632_PERSON_H
#define DIT632_PERSON_H
#include <stdio.h>
#include <stdlib.h>
#define MAX 20 // max size for the structure array attributes
typedef struct Person{
    char personFirstName[MAX]; // person's given Name
    char personLastName[MAX]; // person's family Name
    char personalNumber[MAX]; // person's personalNumber
    char personAddress[MAX]; // person's address
    int personAge; // person's age
} Person;

typedef struct List {
    struct Person person;
    struct List *next;
} List;

void insertPerson(struct Person person);
void printList();
int getNumberOfPersons();
struct Person* getAll();

List *head;
#endif //DIT632_PERSON_H
