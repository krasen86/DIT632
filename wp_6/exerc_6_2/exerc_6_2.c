/* ====================================
File name: exerc_x_x.c (or cpp) TODO update exercise number
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define section
#define num_elems 200
#define THREAD_EXECUTION_ARRAY_FILLING "Executing \"filling the array\"...\n"
#define THREAD_EXECUTION_ARRAY_SORTING "Executing \"sorting the array\"...\n"
#define THREAD_EXECUTION_ARRAY_SEARCHING "Executing \"searching for the number in the array\"...\n"
#define READ_MAX_VALUE_MESSAGE "Enter max value:"
#define READ_NUMBER_MESSAGE "Enter value to find:"
#define NUMBER_FOUND_MESSAGE "\n%d found at location %d.\n"
#define NUMBER_NOT_FOUND_MESSAGE "\n Not found! %d is not present in the list.\n"

/* ==================================== Main program section ====================================== */
/* This program TODO..... */

// Declaration section
int array[200];
int max_value;

void *populateArray(void *param);
void *sort(void *param);
void *findNumber(int *number);
int readNumber();

int main() {
    int number;
    time_t t;
    pthread_t tid;
    pthread_attr_t attr;

    srand((unsigned) time(&t));
    pthread_attr_init(&attr);

    max_value = readNumber(READ_MAX_VALUE_MESSAGE);

    pthread_create(&tid, &attr, populateArray, NULL);
    pthread_join(tid, NULL);

    pthread_create(&tid, &attr, sort, NULL);
    pthread_join(tid, NULL);

    number = readNumber(READ_NUMBER_MESSAGE);

    pthread_create(&tid, &attr, findNumber, &number);
    pthread_join(tid, NULL);

    return 0;
}

int readNumber(char *message) {
    int number;
    printf("%s\n", message);
    scanf("%d", &number);

    return number;
}

void *populateArray(void *param) {
    int c, n;

    printf(THREAD_EXECUTION_ARRAY_FILLING);
    for (c = 0; c < num_elems; c++) {
        for(n=0; n<1000; n++); // To delay a bit
        array[c] = rand() % max_value;
    }

    pthread_exit(0);
}

void *sort(void *param) {
    int c, d, swap;

    printf(THREAD_EXECUTION_ARRAY_SORTING);
    for (c = 0; c < num_elems; c++) {
        for (d = 0; d < num_elems - c - 1; d++) {
            if (array[d] > array[d + 1]) {
                swap = array[d];
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }

    pthread_exit(0);
}

void *findNumber(int *number) {
    int first = 0;
    int last = num_elems - 1;
    int middle = (first + last) / 2;

    int n;
    for(n=0; n<num_elems; n++){
        printf(" %d", array[n]);
    }
    printf("\n");

    printf(THREAD_EXECUTION_ARRAY_SEARCHING);
    while (first <= last) {
        if (array[middle] < *number)
            first = middle + 1;
        else if (array[middle] == *number) {
            printf(NUMBER_FOUND_MESSAGE, *number, middle + 1);
            break;
        } else
            last = middle - 1;

        middle = (first + last) / 2;
    }
    if (first > last)
        printf(NUMBER_NOT_FOUND_MESSAGE, *number);

    pthread_exit(0);
}