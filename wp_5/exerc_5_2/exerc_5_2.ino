/* ====================================
File name: exerc_4_5.ino
Date: 2021-02-18
Group nr 14
Members that contribute to the solutions: Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time:
Demonstration code: 8336
====================================== */

/* --- Macros predefined for the compiler
DDRB  Data direction register B
PORTB Outport B
PINB  Inport B
DDRD  Data direction register D
PORTD Outport D
PIND  Inport D
HIGH ON-1
LOW OFF-0
*/

// Define section
#define NUMBER_OF_ROWS 4 // number of rows in the keypad
#define NUMBER_OF_COLUMNS 4 // number of columns in the keypad
#define DELAY_AFTER_PRESS 500 // default delay after pressing a button
#define ENABLE_OUTPUT_REGISTER 0b00001111 // use to set the DDRB register as output
#define ENABLE_INPUT_REGISTER 0b00000000 // use to set the DDRD register as input
#define NOT_PRESSED 0 // used for checking if a key has not been pressed
#define BAUD_RATE 9600 // define baud rate for serial
#define VOLTAGE_OFFSET 500 // voltage offset for TMP36 in millivolts

/* ==================================== Main program section ====================================== */
/* This program is designed using Tinkercad(image of the circuit can be seen in file's folder) simulation for Arduino Uno.
 * The programme handles reading the keypad buttons the program prints out the pressed key number in the serial monitor and starts a 1s delay,
 * if no key is pressed nothing is printed out. The keypad is designed as a 4-4 Matrix with mapping the buttons as follows 0-9->A-F.
 * */

// Define constants
const unsigned char keypad[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = { // keypad matrix to map the buttons in order 0-9->A-F
        {'0','1','2','3'},
        {'4','5','6','7'},
        {'8','9','A','B'},
        {'C','D','E','F'}
};
const unsigned int columns[NUMBER_OF_COLUMNS] = {7, 6, 5, 4}; // define the column's pins numbers
const unsigned int rows[NUMBER_OF_ROWS] = {11, 10, 9, 8}; // define the row's pins numbers

// Global variables
volatile unsigned char input; // store the pressed button value
volatile unsigned long lastInterrupt;

int analogPin = A0;
int val = 0;
int celsius;

// Set-up section
void setup()
{
    Serial.begin(BAUD_RATE); // start and configure the serial monitor with baud rate
    DDRD = ENABLE_INPUT_REGISTER; // setting the data direction register for port D to input
    DDRB = ENABLE_OUTPUT_REGISTER; // setting the last for bits(pins) of data direction register for port B to output(1s)
    //PORTB = ENABLE_OUTPUT_REGISTER; // set the first 4 rows to HIGH by writing 1s to the corresponding PINs on PORTB outport

    lastInterrupt = 0;
    attachInterrupt(digitalPinToInterrupt(2), checkForKeypadInput, FALLING);
}

// Main Loop
void loop()
{
    //input = checkForKeypadInput(); // continuously call method to see if a keypad button has been pressed and save the value in input


    if(input != NOT_PRESSED){ // check if button has not been pressed
        Serial.println((char) input); // if pressed print the pressed character
        input = NOT_PRESSED;
    }

    val = analogRead(analogPin);
    celsius = (int) (((calculateTemperature(val) - VOLTAGE_OFFSET) * 0.1) + 0.5);

    Serial.println(celsius);


    delay(500);
    PORTB = 0b00000000;
}

// Function to check which keypad button is pressed and return it if any
void checkForKeypadInput()
{
    if (millis() - lastInterrupt > 10) {

        input = NOT_PRESSED; // used to store the found charectred set by default to Not-pressed
        unsigned int i,j; // indexes for the loop iterations

        for(i = 0; i < NUMBER_OF_ROWS; i++){ // start a loop to iterate over the rows
            for(j = 0; j < NUMBER_OF_COLUMNS; j++){ // start iterating over the columns for the current row
                if(digitalRead(columns[j]) == LOW && digitalRead(rows[i]) == LOW){ // check if the column is LOW, when LOW the button that connects row and column is pressed (because of the PULL-UP resistor)
                    input = keypad[i][j]; // key is found and save the value from the matrix in the variable

                }
            }
            digitalWrite(rows[i], HIGH); // set back the current row to HIGH (activate)
        }

        lastInterrupt = millis();
    }
}

float calculateTemperature(int inputVoltageReading) {

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5000mV):
    float milliVoltage = (inputVoltageReading * (5000 / 1024.0));


    return milliVoltage;
}