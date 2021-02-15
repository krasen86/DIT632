/* ====================================
File name: decode.c (or cpp)
Date: 2021-xx-xx TODO update date
Group nr 14IIm
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"

#define TRUE 1
#define FALSE 0
#define ALLOWED_CHARS "0123456789abcdefABCDEF"
#define ENGINE_ON "engine_on: %d \n"
#define GEAR_POS "gear_pos: %d \n"
#define KEY_POS "key_pos: %d \n"
#define BRAKE1 "brake1: %d \n"
#define BRAKE2 "brake2: %d \n"
#define INVALID_HEX "You've provided an invalid hexadecimal number\n"



int validateArgs(int argc, char *argv[]);
unsigned int convertHexToDecimal(char *argv[]);
unsigned int getBits(unsigned int dec_val, int startPos, int numOfBits);


int main(int argc, char *argv[]){
    unsigned int hexValue;
    unsigned int engine_on;
    unsigned int gear_pos;
    unsigned int key_pos;
    unsigned int brake1;
    unsigned int brake2;

    if(validateArgs(argc, argv)){
        hexValue  = (unsigned int) strtol(argv[1], NULL, 16);
        engine_on = getBits(hexValue, 7, 1);
        gear_pos = getBits(hexValue, 4, 3);
        key_pos = getBits(hexValue, 2, 2);
        brake1 = getBits(hexValue, 1, 1);
        brake2 = getBits(hexValue, 0 , 1);
        printf(ENGINE_ON, engine_on);
        printf(GEAR_POS, gear_pos);
        printf(KEY_POS, key_pos);
        printf(BRAKE1, brake1);
        printf(BRAKE2, brake2);
    }else {
        printf(INVALID_HEX);
    }
    return 0;
}

int validateArgs(int argc, char *argv[]){
    if(argc == 2){
        if(strlen(argv[1]) > 0 && strlen(argv[1]) < 3) {
            if (argv[1][strspn(argv[1], ALLOWED_CHARS)] == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

unsigned int getBits(unsigned int value, int startPos, int numOfBits){
    unsigned int bitValue;
    unsigned mask;
    mask = ((1 << numOfBits) - 1) << startPos;
    bitValue = value & mask;
    bitValue = bitValue >> startPos;
    if((startPos == 4 && bitValue > 4) || (numOfBits == 1 && bitValue > 1) || (startPos == 2 && bitValue > 2)) {
        printf(INVALID_HEX);
        exit(0);
    }
    return bitValue;
}