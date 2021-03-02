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
            printf("hye");
            if(isDoorOpen()){
                delay(10);
                closeDoor();
            }else{
                openDoor();
                while(!isDoorOpen());
                printf("Yup");
                delay(10);
                closeDoor();
            }
        }
    }
}

unsigned int getStatus(){
    return 0b1000;
    //return ML13_Status;
}

int isDoorOpen(){
    if(status & 0B10000){
        return FALSE;
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
    // Converting time into milli_seconds
    int milli_seconds = 1000 * time;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds){
        printf("Clocking");
    }

}