#include "person.h"
#include "string.h"


void printList();

int main(){
    Person person;
    strcpy(person.personFirstName,"Krasen");
    strcpy(person.personLastName,"TheKraken");
    insertPerson(person);
    printList();
}

void printList(){
    List *temp = head;
    if(temp == NULL){
        printf("List is empty");
    }else {
        while (temp != NULL) {
            printf("%s\n", temp -> person.personFirstName);
            printf("%s\n", temp -> person.personLastName);
            temp = temp -> next;
        }
    }
}