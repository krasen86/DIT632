/* ====================================
File name: code.c (or cpp)
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
    unsigned int hexDec;
    unsigned int engine_on;
    unsigned int gear_pos;
    unsigned int key_pos;
    unsigned int brake1;
    unsigned int brake2;

    if(validateArgs(argc, argv)){
        hexDec = convertHexToDecimal(argv);
        engine_on = getBits(hexDec, 7, 1);
        gear_pos = getBits(hexDec, 4, 3);
        key_pos = getBits(hexDec, 2, 2);
        brake1 = getBits(hexDec, 1, 1);
        brake2 = getBits(hexDec, 0 , 1);
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

unsigned int convertHexToDecimal(char *argv[]){
    // https://www.geeksforgeeks.org/program-for-hexadecimal-to-decimal/
    char *hexChar = argv[1];
    int len = strlen(argv[1]);

    // Initializing base value to 1, i.e 16^0
    int base = 1;
    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i=len-1; i>=0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexChar[i]>='0' && hexChar[i]<='9')
        {
            dec_val += (hexChar[i] - 48)*base;
            // incrementing base by power
            base = base * 16;
        }
            // if character lies in 'A'-'F' , converting
            // it to integral 10 - 15 by subtracting 55
            // from ASCII value
        else if (hexChar[i]>='A' && hexChar[i]<='F')
        {
            dec_val += (hexChar[i] - 55)*base;
            // incrementing base by power
            base = base*16;
        }
        else if (hexChar[i]>='a' && hexChar[i]<='f'){
            dec_val += (hexChar[i] - 87)*base;
            // incrementing base by power
            base = base*16;
        }
    }

    return dec_val;
}

unsigned int getBits(unsigned int dec_val, int startPos, int numOfBits){
    unsigned int bitValue;
    unsigned mask;

    mask = ((1 << numOfBits) - 1) << startPos;
    bitValue = dec_val & mask;
    bitValue = bitValue >> startPos;
    if((startPos == 4 && bitValue > 4) || (numOfBits == 1 && bitValue > 1) || (startPos == 2 && bitValue > 2)) {
        printf(INVALID_HEX);
        exit(0);
    }
    return bitValue;
}