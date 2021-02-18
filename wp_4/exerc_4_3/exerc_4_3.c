/* ====================================
File name: decode.c (or cpp)
Date: 2021-02-18
Group nr 14IIm
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 8336
====================================== */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DISPLAY_PRESSED_NUMBER " -------- Pressed key value base 10 = %d -------- Pressed key value base 16 = %X \n" // String that prints the decimal and hexadecimal value of the pressed key
#define DISPLAY_PORT_BINARY "Port value binary:" // Start message for displaying binary

/* ==================================== Main program section ====================================== */
/* This program simulates the behavior of reading input from keyboard without any hardware assistance.
 * Specifically, when a key is pressed on the keyboard an 8-bit value is saved in a specific register
 * address, from which the first 4 bits comprise the value of a pressed key (0-15), whereas the last
 * bit (place 7 in the register) specifies whether the key was down when the register is read, by
 * being 0, otherwise the bit 7 is set to 1.
 * */

void f_delay(int);
unsigned char random_inport( void);
void printPort(int portValue, unsigned int pressedNumber );
unsigned int getBits(unsigned char port, int numOfBits);

int main(){
    unsigned char port;
    unsigned int number;
    srand(time(0));
    // main loop for keep 'reading' for simulated input
    while (1) {
        port = random_inport();
        if ((port >> 7) == 0b0) { // check if the bit 7 in the register is pressed by comparing its value equal to 0
            number = getBits(port, 4); // get the binary representation of the bits that specify the value of a pressed key, i.e. last 4 bits
            printPort(port, number); // display the pressed key's port number and its value
        }
        f_delay(5);
    }
}

// Function to get the specific bits needed from a provided binary value
unsigned int getBits(unsigned char port, int numOfBits){
    unsigned int bitValue; // store the value into an integer
    unsigned mask; // store the bit values that we want to keep from the initial number
    mask = ((1 << numOfBits) - 1); // mask used in order to isolate the last 4 bits from the number
    bitValue = port & mask; // save the port and mask values into the bitValue applying bitwise AND
    return bitValue; // return the value to the function call
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
    printf(DISPLAY_PORT_BINARY); // Print message for displaying port binary notification
    // Print bits and at the end corresponding decimal value
    for(j =i-1 ;j > -1;j--)
        printf("  %d",binChar[j]);
    printf(DISPLAY_PRESSED_NUMBER, pressedNumber, pressedNumber); // displaying the decimal and hexadecimal value of the pressed key
}


