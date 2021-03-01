// Skeleton for exercise nr 5 in WP 6 course DIT632.
// File skeleton_exerc_6_5.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t  not_full = PTHREAD_COND_INITIALIZER;

// Global buffer and corresponding counters.
char  letter = 'a'; //the starting letter
#define MAX 10//buffer size
unsigned short count = 0;
char buffer[MAX]; // circular buffer
int inpos = 0; // index for next character to be put in buffer (put)
int outpos = 0; // index for next character to be read ( fetch )

void *put();
void *fetch();

int main(){
    int i;
    pthread_t putThreadId;
    pthread_t fetchThreadId;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&putThreadId, &attr, put, NULL);
    pthread_create(&fetchThreadId, &attr, fetch, NULL);

    while(1){
        //printf("Main is executing...");

    }

}


void *put(){
    while(1){
        pthread_mutex_lock(&count_mutex);
        if(pthread_cond_wait(&not_full, &count_mutex)) {
            if (count < 10) {
                buffer[inpos] = letter;
                printf("Buffer store\n");
                if (letter == 'z') {
                    letter = 'a';
                } else {
                    letter++;
                }
                if (inpos == MAX - 1) {
                    inpos = 0;
                } else {
                    inpos++;
                }
                count++;
                pthread_cond_signal(&not_empty);
            }
        }
        pthread_mutex_unlock(&count_mutex);
    }
}


void *fetch(){
    while(1){
        pthread_mutex_lock(&count_mutex);
        if(pthread_cond_wait(&not_empty, &count_mutex)) {
            if (count > 0) {
                printf("%c\n", buffer[outpos]);
                if (outpos == MAX - 1) {
                    outpos = 0;
                } else {
                    outpos++;
                }
                count--;
                pthread_cond_signal(&not_full);
            }
        }else{
            pthread_cond_signal(&not_full);
        }
        pthread_mutex_unlock(&count_mutex);
    }
}

#pragma clang diagnostic pop