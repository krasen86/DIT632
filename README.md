# DIT632 - Assignments and Work Products - Group 14

## Work package 1

[Here](./wp_1/) you can find the descriptions for the first work package exercises.

[Exercise 1](wp_1/exerc_1_1/exerc_1_1.c): Reads in an integer number between 1 and 5 from the keyboard and prints out one of existing five sentences on the console depending on what number was entered. 

[Exercise 2](wp_1/exerc_1_2/exerc_1_2.c): Count the number of words in a sentence.

[Exercise 3](wp_1/exerc_1_3/exerc_1_3.c): String encryption algorithm for ASCII characters shifting.

[Exercise 4](wp_1/exerc_1_4/exerc_1_4.c): Guess the number game with rand() function.

## Work package 2

[Here](./wp_2/) you can find the descriptions for the second work package exercises.

[Exercise 1](wp_2/exerc_2_1/exerc_2_1.c): Copy a given string, strcpy()

[Exercise 2](wp_2/exerc_2_2/exerc_2_2.c): Create and print a random integer array by use of pointers

[Exercise 3](wp_2/exerc_2_3/exerc_2_3.c): Compare two strings provided from the command line with strcmp() and without.

[Exercise 4](wp_2/exerc_2_4/exerc_2_4.c): Checks if the string is a palindrome.

[Exercise 5](wp_2/exerc_2_5/exerc_2_5.c): Creates a random array and calculates the frequency of the numbers and plots a histogram

[Exercise 6](wp_2/exerc_2_6/exerc_2_6.c): Creates a "que" with array[] and populates the que and has a input adn output method

[Exercise 7](wp_2/exerc_2_7/exerc_2_7.c): The programme checks if a given personal number is valid

[Exercise 8](wp_2/exerc_2_8/exerc_2_8.c): Nim game - Two players take in turn between one and three coins from the stack. Whoever are forced to take the last coin have lost. The program allows quitting at any step by inputting 'q'.

## Work package 3

[Here](./wp_3/) you can find the descriptions for the third work package exercises.

[Exercise 1](wp_3/exerc_3_1/exerc_3_1.c): Move robot in a given direction. Uses structure for robot and simulates movement on it.

[Exercise 2](wp_3/exerc_3_2/exerc_3_2.c): Sorts a given array with enhanced bubble sort and searches(linear) for a given number. -> readNumber(), inputValidationInteger()

[Exercise 3](wp_3/exerc_3_3/exerc_3_3.c): Double linked list containing integers, addFirst()

[Exercise 4](wp_3/exerc_3_4/exerc_3_4.c): File management(binary) with person structure and uses of header file for personal number( implementation contains getIntegerValue from a char). createFile(), writeToFile, readFromFile

## Work package 4

[Here](./wp_4/) you can find the descriptions for the fourth work package exercises.

[Exercise 1](wp_4/exerc_4_1/code.c): Encoding a given integers arguments to hexadecimal value by using bit manipulation. bit-shifting 

[Exercise 2](wp_4/exerc_4_2/decode.c): Decode a given hexadecimal to their binary value and extract the bits from that value. strtol(base 16), int getBits(unsigned int value, int startPos, int numOfBits) -- hexadecimal

[Exercise 3](wp_4/exerc_4_3/exerc_4_3.c): Check if a given port-bit is pressed and print the value of the register.

[Exercise 4](wp_4/exerc_4_4/exerc_4_4.ino): TinkerCad -- 8 LEDs that rotate clockwise, a switch that starts/stops the shifting of the LEDs, uses bit-shifting -- Pull-UP resistor

[Exercise 5](wp_4/exerc_4_5/exerc_4_5.ino): TinkerCad -- Keypad printing the pressed key, columns input and rows set to output - PULL-UP

## Work package 5

[Here](./wp_5/) you can find the descriptions for the fifth work package exercises.

[Exercise 1](wp_5/exerc_5_1/exerc_5_1.ino): TinkerCad -- Keypad printing the pressed key by using interrupt connected to a logical AND gate, columns input and rows set to output - PULL-UP

[Exercise 2](wp_5/exerc_5_2/exerc_5_2.ino): TinkerCad -- Temperature sensor and Keypad. Analog reading for temperature sensor displaying the reading in Celsius. Printing the pressed key by using interrupt connected to a logical AND gate, columns input and rows set to output - PULL-UP, calculates temperature in celsius and delay interrupt

## Work package 6

[Here](./wp_6/) you can find the descriptions for the sixth work package exercises.

[Exercise 1](wp_6/exerc_6_1/exerc_6_1.txt): Answers to the questions about the skeleton code [*sortandfind_20.c*](skeleton/sortandfind_20.c) (about threads' execution etc). 

[Exercise 2](wp_6/exerc_6_2/exerc_6_2.c): Rewriting the previous skeleton code ([*sortandfind_20.c*](skeleton/sortandfind_20.c)), but this time using 3 different threads for each of the 3 major operations (filling the array, sorting it and finally searching in the array for a number using binary search).

[Exercise 3](wp_6/exerc_6_3/exerc_6_3.c): 'Mocking' a subsystem for an automatic door in order to do the logical thinking of how an automatic door should work. `Bitwise AND` was used to check the value in status that has the sensor is true, when something is detected. Also, a delay function was written `delay(int time){...}`.

[Exercise 4](wp_6/exerc_6_4/exerc_6_4.c): Controlling events in a program, by executing two threads in order to run two
different "processes" concurrently, while having access to a commonly accessed, ***global system time variable***. 

[Exercise 5](wp_6/exerc_6_5/exerc_6_5.c): Two threads simulating the functionality of a circular buffer in which one of the threads inserts letters from the alphabet to the buffer, whereas the second thread prints the letters from the buffer to the terminal. Each of the threads uses **signaling** in order to make sure that the program does not print duplicate values and/or fill the buffer passed its maxed value.

Excerpt of function calls used: `pthread_mutex_lock(&countMutex)`, `pthread_cond_wait(&notFull, &countMutex)`, `pthread_cond_signal(&notEmpty)`, `pthread_mutex_unlock(&countMutex)`
