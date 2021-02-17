/* ====================================
File name: exerc_x_x.c (or cpp) TODO update exercise number
Date: 2021-xx-xx TODO update date
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: xxxx TODO replace with code from TA
====================================== */

// Include section
#include "stdio.h"

// Define section


/* ==================================== Main program section ====================================== */
/* This program TODO..... */


const char keypad[4][4] = {
        {'1','2','3', 'A'},
        {'4','5','6', 'B'},
        {'7','8','9', 'C'},
        {'*','0','#', 'D'}
};

const int columns[4] = {7, 6, 5, 4};
const int rows[4] = {11, 10, 9, 8};

char input;


void setup()
{
    Serial.begin(9600);
    DDRD = 0b00000000;
    DDRB = 0b00001111;
}

void loop()
{
    input = readInput();
    if(input != 0){
        Serial.println(input);
        delay(1000);
    }
}

char readInput()
{
    char returnValue = 0;

    for(int i = 0; i<4; i++){
        digitalWrite(rows[i], HIGH);
        for(int j = 0; j<4; j++){
            if(digitalRead(columns[j]) == HIGH){
                returnValue = keypad[i][j];
            }
        }
        digitalWrite(rows[i], LOW);
    }
    return returnValue;
}