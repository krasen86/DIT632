// Skeleton for exercise nr 5 in WP 6 course DIT632.
// File skeleton_exerc_6_5.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t  not_full = PTHREAD_COND_INITIALIZER;

#define MAX 10//buffer size
#define MAIN_THREAD_PRINT "Main is executing\n"
#define PUT_THREAD_PRINT "Buffer store\n"
#define FETCH_THREAD_PRINT "Buffer output: %c\n"
#define BUFFER_FULL_STRING "Buffer full\n"
#define FIRST_LETTER 'a'
#define LAST_LETTER 'z'

// Global buffer and corresponding counters.
char  letter = FIRST_LETTER; //the starting letter
unsigned short count = 0;
char buffer[MAX]; // circular buffer
int inpos = 0; // index for next character to be put in buffer (put)
int outpos = 0; // index for next character to be read ( fetch )

void *put();
void *fetch();
void wait(int loops);

int main(){
    int i = 0;
    pthread_t putThreadId;
    pthread_t fetchThreadId;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&putThreadId, &attr, put, NULL);
    pthread_create(&fetchThreadId, &attr, fetch, NULL);

    while(1){
        wait(5000000);
        printf(MAIN_THREAD_PRINT);
    }

}

void wait(int loops){
    int i = 0;
    while(i < loops) {
        i++;
    }
}


void *put(){
    while(1){
        pthread_mutex_lock(&count_mutex);
        while(count > 0) {
            pthread_cond_wait(&not_full, &count_mutex);
        }
        if (count < 10) {
            buffer[inpos] = letter;
            printf(PUT_THREAD_PRINT);
            if (letter == LAST_LETTER) {
                letter = FIRST_LETTER;
            } else {
                letter++;
            }
            if (inpos == MAX - 1) {
                inpos = 0;
            } else {
                inpos++;
            }
            count++;
            wait(3000000);
            pthread_cond_signal(&not_empty);
        }else{
            printf(BUFFER_FULL_STRING);
        }
        pthread_mutex_unlock(&count_mutex);
    }
}


void *fetch(){
    while(1){
        pthread_mutex_lock(&count_mutex);
        while(count == 0) {
            pthread_cond_wait(&not_empty, &count_mutex);
        }
        if (count > 0) {
            printf(FETCH_THREAD_PRINT, buffer[outpos]);
            if (outpos == MAX - 1) {
                outpos = 0;
            } else {
                outpos++;
            }
            count--;
            pthread_cond_signal(&not_full);
        }else{
            wait(3000000);
            pthread_cond_signal(&not_full);
        }
        pthread_mutex_unlock(&count_mutex);
    }
}
