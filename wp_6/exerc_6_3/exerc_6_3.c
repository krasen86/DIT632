#include <stdio.h>
#include <time.h>

#define ML13_Status 0x0B10
#define ML13_Control 0x0B00
#define TRUE 1
#define FALSE 0
#define CLOSE_DOOR 0x0B10
#define OPEN_DOOR 0x0B01

int isDoorOpen();
void delay(int time);
void closeDoor();
void openDoor();
unsigned int getStatus();

unsigned int status;
unsigned int control;

int main () {
    closeDoor();
    while(1){
        status = getStatus();
        if(status & 0b1000) {
            if(isDoorOpen()){
                delay(5);
                closeDoor();
            }else{
                openDoor();
                while(!isDoorOpen());
                delay(5);
                closeDoor();
            }
        }
    }
}

unsigned int getStatus(){
    return ML13_Status;
}

int isDoorOpen(){
    if(status & 0B10000){
        return TRUE;
    }else{
        return FALSE;
    }
}

void closeDoor(){
    control = CLOSE_DOOR;
}

void openDoor(){
    control = OPEN_DOOR;
}

void delay(int time){
    clock_t currentTime = 0;
    clock_t startTime = clock() / CLOCKS_PER_SEC;

    while (currentTime < startTime + time){
        currentTime = clock() / CLOCKS_PER_SEC;
    }
}