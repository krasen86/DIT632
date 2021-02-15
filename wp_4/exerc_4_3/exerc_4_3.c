/* *******************************
Program file : bit_manage_function.c
Peter Lundin / 2016-01-97
For test IO program function

******************************** */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_PRESSED_NUMBER " --------Port value base 10 = %d | Port value base 16 = %X \n"

void f_delay(int);
unsigned char random_inport( void);
void printPort(int portValue, unsigned int pressedNumber );
unsigned int getBits(unsigned char port);

int main(){
    int nr;
    unsigned char port;
    unsigned int number;
    srand(time(0));
    while (1){
        port = random_inport();
        if ((port >> 7) == 0b0) {
            number = getBits(port);
            printPort(port, number);
        }
        f_delay(5);
    }
}
unsigned int getBits(unsigned char port){
    unsigned int bitValue;
    unsigned mask;
    mask = ((1 << 4) - 1);
    bitValue = port & mask;
    return bitValue;
}

void f_delay( int tenth_sec){
    clock_t start_t, end_t;
    long int i;
    start_t = clock();
    do{
        for(i=0; i< 10000000; i++);
        end_t = clock();
    }while ((end_t - start_t) < (tenth_sec*CLOCKS_PER_SEC)/10);
}

unsigned char random_inport( void){
    unsigned char inport = 0;
    inport = rand() % 256;
    return (inport);
}

void printPort(int portValue, unsigned int pressedNumber ){
    int binChar[8],j, i=0;

    while(portValue!=0){
        binChar[i++]= portValue % 2;
        portValue = portValue / 2;
    }
    // Fill to 8 bits
    while( i<8){
        binChar[i++]=0;
    }
    // Print bits and at the end corresponding decimal value
    for(j =i-1 ;j > -1;j--)
        printf("  %d",binChar[j]);
    printf(DISPLAY_PRESSED_NUMBER, pressedNumber, pressedNumber);
}


