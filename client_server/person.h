//
// Created by krasen on 2021-03-05.
//

#ifndef DIT632_PERSON_H
#define DIT632_PERSON_H

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

#endif //DIT632_PERSON_H
