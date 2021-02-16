/* ====================================
File name: exerc_X_X.c
Date: 2020-XX-XX
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: [<Ass code 1-4> <abc>]
====================================== */

// ---- Program template for Arduino in Tinkercad VT 2020
#include <avr/io.h>
#include <util/delay.h>

/* --- Macros preedefind for the compiler
DDRB  Data direction register B
PORTB Outport B
PINB  Inport B
DDRD  Data direction register D
PORTD Outport D
PIND  Inport D
*/

unsigned char input;

void setup() {
    Serial.begin(9600);
    DDRD = 0b11111111; // setting the data direction register for port D to output
    // If use of Serial monitor Sets pin 2-7 as output-bits and Pin 1 and 0 as 10.
    DDRB = 0b00000000; // setting the data direction register for port B to input
    PORTD = 0b00000011;

    PINB = PB0;
}


void loop() {

    input = PINB;

    if (input == LOW) {
        if (PORTD == 0b11000000) {
            PORTD = 0b10000001;
        } else if (PORTD == 0b10000001) {
            PORTD = 0b000000011;
        } else {
            PORTD = PORTD << 1;
        }
    }

    delay(500); // Wait for 500 millisecond(s)
}