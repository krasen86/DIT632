/* ====================================
File name: exerc_4_4.c
Date: 2020-XX-XX // TODO .....
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: [<Ass code 1-4> <abc>] // TODO....
====================================== */

// ---- Program template for Arduino in Tinkercad VT 2020
#include <avr/io.h>
#include <util/delay.h>

/* --- Macros predefined for the compiler
DDRB  Data direction register B
PORTB Outport B
PINB  Inport B
DDRD  Data direction register D
PORTD Outport D
PIND  Inport D
*/



/* ==================================== Main program section ====================================== */
/* This program is designed using Tinkercad simulation for Arduino Uno. The programme starts with 2 LEDs ON(out of 8)
 * and when the switch is turned ON the LEDs start to shift by one and rotate, when the last LED is ON the ration starts
 * the first LED is set to ON and, after the rotation is repeated continuously while the switch is ON. When the switch is
 * turn back off the shifting stops and the last 2 LEDs stay ON.
 * */

// Define section
#define START_LED_VALUE 0b00000011 // binary used to as start state for LEDs, first 2 LEDs are ON
#define ROTATION_LED_STATE 0b10000001 // binary used to as rotation state for LEDs, first and last ones are ON
#define END_LED_VALUE 0b11000000 // binary used to for the checking if the last 2 LEDs are currently ON in order to see if rotation should start
#define DELAY 500 // delay between shifting the LEDs
#define SHIFTING_INDEX 1 // Number of LEDs to shift left
#define ENABLE_OUTPUT_REGISTER 0b11111111 // use to set the DDRD register as output
#define ENABLE_INPUT_REGISTER 0b00000000 // use to set the DDRB register as input
//#define INPORT_B0 8 // used to read the digital pin 8

// Global variables
unsigned char input; // used to read and store the input value from the switch

//Set up section
void setup() {
    DDRD = ENABLE_OUTPUT_REGISTER; // setting the data direction register for port D to output(1s)
    DDRB = ENABLE_INPUT_REGISTER; // setting the data direction register for port B to input
    PORTD = START_LED_VALUE; // set the first 2 LEDs to on by writing 1s to the corresponding PINs on PORTD outport
}

// Main Loop
void loop() {
    input = PINB; // Read continuously the value from the switch from the inPort of pin PB0
    //input = digitalRead(INPORT_B0); // Read continuously the value from the switch from the inPort of pin PB0
    if (input == LOW) { // check if the input is LOW since the resistor is set as Pull-UP where the reading is inverted and ON switch is LOW
        if (PORTD == END_LED_VALUE) { // Handle case where last 2 LEDs are on
            PORTD = ROTATION_LED_STATE; // Set the last and the first LEDs to ON (start rotation)
        } else if (PORTD == ROTATION_LED_STATE) { // Handle case where last and first LED is ON
            PORTD = START_LED_VALUE; // set the LEDs to start state, first 2 LEDs are ON (complete rotation)
        } else { // base case
            PORTD = PORTD << SHIFTING_INDEX; // shift the LEDs by the defined value
        }
    }
    delay(DELAY); // Wait for 500 millisecond(s)
}