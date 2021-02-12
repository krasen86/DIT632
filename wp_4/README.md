# Work package nr 4 / Low level C-programming

## Exerc_4_ 1 (Filename code.c) (2p)

Pack and unpack variables into a byte. You need to store 4 different values in a byte. The values are:

| Name      | Range | Bits  | Info
| ---       | ---   | ---   | ---
| engine_on | 0..1  | 1     | Is engine on or off . This is bit no 7 (MSB)
| gear_pos  | 0..4  | 3     | Which gear position do we have
| key_pos   | 0..2  | 2     | Which position is the key in
| brake1    | 0..1  | 1     | Are we breaking (provided by sensor 1)
| brake2    | 0..1  | 1     | Are we breaking (provided by sensor 2) = bit no 0 (LSB)



We should store them in a byte like this:

| [engine_on]   | [gear_pos] | [key_pos] | [brake1] | [brake2] |    |
| ---           | ---        | ---       | ---      | ---      | --- |
| 1 bit         | 3 bits     | 2 bits    | 1 bit    | 1 bit    | (LSB, Least significant bit )

(8 bits in total)

<br>

Write a program **code.c** which takes 5 arguments (more or less than 5 arguments should be treated as an error). The arguments should correspond to the values/variables above. <br>
Example for a start of the program from command line:
<br>
&emsp; &emsp; &emsp; `code   1 2 2 1 1`

The above should be treated as:

| Name      | Value | Bits     | 
| ---       | ---   | ---      |
| engine_on | 1     | Bit no 7 |
| gear_pos  | 2     |          |
| key_pos   | 2     |          |
| brake1    | 1     |          |
| brake2    | 1     | Bit no 0 |


The program should pack these values together in a byte (unsigned char) and print it out to the console in hexadecimal form. For this example, it should be ‘AB’ corresponding to bits ‘10101011. After printing out the code to the console, the program should exit. The program should be fail-safe, i.e. if it finds anything wrong (too many/few arguments, faulty input values) your program should
print out an error message and exit.

<br>
<hr>

## Exerc_4_ 2 (decode.c) (2p)

Write a program **decode.c** that takes 1 argument (one argument, hexadecimal number) and prints out the bit positions for the engine, gear, etc. In the example of ‘AB’ (again, make it fail-safe). The
argument should correspond to the decoded byte, e.g. as printed by code.c . If your program finds anything wrong (too many/few arguments, faulty input values) your program should print out an error message and exit.

The program should unpack the bytes according to the specification above. Print out the result as  below:

| Name      | Value|
| ---       | ---  |
| engine_on |      |
| gear_pos  |      |
| key_pos   |      |
| brake1    |      | 
| brake2    |      | 

For example, start program in the console window : <br>
&emsp; &emsp; &emsp; `decode AB`

and the result should be:


| Name      | Value|
| ---       | ---  |
| engine_on |  1   |
| gear_pos  |  2   |
| key_pos   |  2   |
| brake1    |  1   | 
| brake2    |  1   | 

<br>
<hr>

## Exerc_4_3 (Filename exerc_4_3.c) (2p)

In this exercise, you shall design a general C-program that reads a smart keyboard including internal 8 bits registers. The keyboard is connected to the CPU and all keyboards registers can be accessed by reading or writing to the register specific address.

The program can read the value of a pressed key on the keyboard as an 8-bit value in a register with a specific address.

The value (0-15) of a pressed key is the value of bit 0 – 3 in the register. If a key is down when the register is read bit 7 (DAV in figure) is zero otherwise the bit 7 is set (1).


In figure the key with the value 6 is down for the moment.
[<img src="../images/Table figure exerc_4_3.png">](../images/wp_4/Table%20figure%20exerc_4_3.png)
If no key pressed when reading the register DAV bit is set (1).

To simulate this reading of the keyboard without any hardware for a general C-program we will use help-functions from the course folder. You can find these at the course homepage in **Files/Course week #4**.

**In the file : bit_manage_func.c** you can find the following functions:

**void f_delay(int tenth_sec)** : Gives a time delay for a number of tenths of a second.

**unsigned char random_inport(void)** : Generates a random value 0 – 255.

This will simulate the read value from a 8 bit inport in a system.

**void printport(int portvalue)** : Prints out the binary pattern and the decimal value for a char of value 0 – 255.

In reality, the keyboard is controlled by a hardware, and to read a pressed key number you read the 8-bit value in a register at a specific address. In our case, in this exercise, we simulate this by call the function **random_inport()**.

The value in the register should be interpreted as follows: If bit no 7 is zero there is a key pressed and the key nr (0 – 15) can be read as bit 0 to 3 in the value. The value on bit no 4 to 6 is of no interest and its value should not affect the program function.

**Write a program** that periodically (e.g. once every half second) reads the keyboard register (the random number). If a key is pressed (bit-7) read the key nr and print it out on the console in hexadecimal form 0 – 9, A- F. If no key pressed there shouldn’t be any printout.

<br>
<hr>

## Exerc_4_4 ( File name exerc_4_4.c) (2p)

In ThinkerCad you should draw a new circuit as the figure on next page shows. In the circuit PD0-PD7 is used as output bits and connected to the LED:s anode side via a resistor (1kOhm). Bit PB0 is used as an in-bit reading the status from one side of a DIP switch. The value to PB0 will be either 1 or 0 depending on if the DIP switch is on or not.

The circuit is designed as figure to right shows. A high (1, (5V)) value on an out-bit on PD will light up the diode.
[<img src="../images/Exerc_4_4%20Figure.png">](../images/wp_4/Exerc_4_4%20Figure.png)

Write a program with the function described below that uses out- and in-port as described above.

The code should be written in C (even though one could use a block-diagram in TinkerCad).

**The program should work as follows:**

1. Configure the PORTB as input port and PORTD as output port.
2. Write 3 (binary 0000 0011) to PORTD.
3. In an infinitive loop:
   Read bit PB0 on the IN_PORTB
    - If bit is set (1) rotate the content on OUT-port one step left. If bit 7 on PORTD is   set before the left shift bit 0 should be set after the shift (we rotate the content).
    - If bit is clear (0). Do not change the value on OUT-port.
  
For the delay use the delay function as shown in the program skeleton below.


You should use the predefined macros for reading/writing to the registers and in/out ports. You should use PORTx when writing out values and PINx for reading the same port if configured as input port. Just like we used the pins during the lecture. You shall use the predefined structure with the two functions setup() and loop(). Run the program in the simulator to test the function.

[<img src="../images/Exerc_4_4%20Figure%202.png">](../images/wp_4/Exerc_4_4%20Figure%202.png)

**Note** : If you get some problems it can help using the debugger. Before start set a break point. There is also a possible to connect a Multimeter to any part of the circuit. Depending of our use of bit PD1 and PD0 we can ́t use the serial monitor for printing. 

When ok you just copy the code to any editor and add necessary information in the program head, save it and hand it in as usually together with the other solutions.

```c
// ---- Program template for Arduino in Tinkercad VT 2021

#include <avr/io.h>
#include <util/delay.h>

/* --- Macros predefined for the compiler
DDRB Data direction register B
PORTB Outport B
PINB Inport B
DDRD Data direction register D
PORTD Outport D
PIND Inport D
*/

unsigned char input;
void setup() {
   Serial.begin(9600); // If using the Serial monitor and in that case 
                       // needed Port D bit 1,0 to be set as out/in
   DDRD = 0xFF To set all Port D bits as outbits.
   DDRB= ....... (Set all to inbits)
}

void loop() {
// ------ Main loop-------

delay(500); // Wait for 500 millisecond(s)

}
```

<br>
<hr>

## Exerc_4.5 (Filename: exerc_4_5.c): Keyboard scanning. (3p)

Some cheap keyboards are not connected to a supporting hardware with register for reading the key number. This simpler device is a bit harder to read. In TinkerCad you can connect such a simple keyboard (Figure) to Arduino Uno and then design a program that reds a pressed key number.

[<img src="../images/Exerc_4_5%20Figure%201.png">](../images/wp_4/Exerc_4_5%20Figure%201.png)


**The principle for the keyboard and reading a key.**

The keyboard is built up by four row connectors and four column connectors. At the 16 crosses between raw and column there is normally no electrical connection. At each cross there is a key and if a key is pressed there will be an electrical connection between the column and raw. (See figure below)

The rows (row 1 to row 4) is possible to connect to anything via the four left bits in the flat connector. On the four right bits the four columns are possible to connect to anything.

[<img src="../images/Exerc_4_5%20Figure%202.png">](../images/wp_4/Exerc_4_5%20Figure%202.png)

The keyboard can be connected to any of Arduino ́s IO-ports. One possibility is to connect all 8 row/columns to Port D and configure the port D as 4 bit out/four bit in. 

If we chose this way of connecting the keyboard it will be a bit more tricky than necessary to develop the program for reading the keyboard. This is depending of the possibility to use the same physical IO-port as IN or OUT on bit level. We will also lose the possibility to use the serial monitor for printing out some control text.

Instead we chose to connect the keyboard by connecting the rows to Arduino Port B (bit 0 – 3 ) and the Columns to Port D ( bit 0 – 3 ) . By this we can use Port B as outport and Port D as inport.

To ensure the level (electric) of the columns, when no key is pressed, you normally connect them to 5V via a resistor (so called “pull up resistor”). You can see this in the figure above.

**Your task:**

In Tinkercad you should design a new circuit as described above and shown in the figure to right. We will later expand the circuit so it ́s good to design it as the figure shows. 

You should then, also in Tinkercad, develop a program reading the keyboard system above. The program should print out the key number in the serial monitor if a key is pressed. If no key is pressed there should be nothing printed out.

The program structure should be as below. You should also use the predefined macros as in earlier exercises.

You can use the function Serial.println() for
printing on the monitor.

```
- configure the IO ports
- in an infinity loop
   Call a function checking if any key is pressed and if it should return it ́s value.
   If a key was pressed print out the key value ( 0-9 , A-F) on the serial monitor.
   Delay for one second.
```

Demonstrate for TA and hand in the solution as for exercise 4_4.

**IMPORTANT! You are not allowed to use <keypad.h> library in this exercise!**

<br>
<hr>
