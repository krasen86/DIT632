/* ====================================
File name: exerc_3_1.c
Date: 2020-XX-XX // TODO ..
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: [<Ass code 1-4> <abc>] // TODO ....
====================================== */

// Include section
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define section
#define X_AXIS 'x' // string to specify the "x" axis in the coordinate system
#define Y_AXIS 'y' // string to specify the "y" axis in the coordinate system
#define PROMPT_USER_STARTING_POSITION "Please enter the starting position for the robot (0-99):\n %c axis: " // string to ask for the starting position for a specific axis from the user
#define SIZE_USER_INPUT 50 // Used to set the size of the array for the user's input
#define INVALID_INPUT "Not valid, please try again \n" // Invalid input prompt
#define EXIT_CHAR 'q' // Character for exiting the program
#define EXIT_MESSAGE "Exiting the program...\n" // String to be printed when exiting the program
#define LOWER_POSITION_BOUND 0 // Lower accepted value for the position in the coordinates system
#define UPPER_POSITION_BOUND 99 // Upper accepted value for the position in the coordinates system
#define VALUE_OUT_OF_BOUNDS "You entered a value that is invalid as for the coordinates. Please enter a value between 0-99 next time!\n" // String to notify the user that they have entered an out of bounds values
#define INVALID_COMMAND "You have entered an invalid command as for the robot to follow. Please enter a string that contains only \"m\" and/or \"t\" values for the command!\n" // String to notify the user about an incorrect input command
#define PROMPT_FOR_USER_DIRECTIONS "Please enter a command for the robot to follow! Type a string containing \"m\" for moving towards the current direction and/or \"t\" to turn 90 degrees clockwise!\n" // String to prompt for the user's test command to move the robot
#define INVALID_INPUT_EMPTY_LINE "A simple [enter] is not a valid input! Please try again!\n" // String to notify the user that an empty line is not accepted
#define MOVE_FORWARD 'm' // Accepted value for the robot to move forward
#define TURN_90_DEGREES_CLOCKWISE 't' //  Accepted value for the robot to turn clockwise for 90 degrees
#define PROMPT_FOR_ANOTHER_TEST_CASE "\nDo you want to execute another test case? (Y/N)\n" // String to ask the user about
#define PRINT_INITIAL_ROBOT_COORDINATES "\nInitial position of the robot:\nX: %d, Y: %d, Direction: %s\n" // String to notify the user about the robot's initial position, before running the test case
#define PRINT_FINAL_ROBOT_COORDINATES "Final position after receiving the command \"%s\":\nX: %d, Y: %d, Direction: %s\n" // String to notify the user about the robot's final position, after executing the test case
#define PRINT_BLOCK_SPACING "\n=====================================================\n" // String to be printed for formatting reasons
#define FALSE 0 // define boolean false
#define TRUE 1 // define boolean true

/* ==================================== Main program section ====================================== */
/* TODO .... write description
 *
 */

enum DIRECTION {North , East, South, West}; // Declaration of enum for the robot's directions

// Declaration of the robot struct, with the corresponding coordinates for the X and Y position of the robot, as well as its direction
typedef struct{
    int positionX;
    int positionY;
    enum DIRECTION direction;
}ROBOT;

ROBOT move(ROBOT robot); // make the robot move forward
ROBOT turn(ROBOT robot); // make the robot turn clockwise
int readPosition(char axis); // read the position for an axis from the user
char *readSimulationInstruction(); // read the test case command which specifies the changes of the robot's direction from the user
ROBOT processSimulation(const char *testCaseString, ROBOT robot); // process the entered string which is responsible to alter the robot's direction
int runAnotherSimulation(); // prompt the user for running the program for executing another test case
void clear_stdin(); // Function to clear the stdin buffer
char *checkDirection(int intDirectionRepresentation); // correlate the enum's direction representation to the corresponding direction string, i.e.: 0 == North, and return the string

int main() {
    // Variable declarations
    ROBOT robot; //
    char *testCaseString;

    do {
        robot.direction = North; // initialize the robot's direction and set it towards the North
        robot.positionX = readPosition(X_AXIS); // read robot's X axis value from the user
        robot.positionY = readPosition(Y_AXIS); // read robot's Y axis value from the user

        testCaseString = readSimulationInstruction(); // read the instruction command string from the user and assign it to a variable

        printf(PRINT_INITIAL_ROBOT_COORDINATES, robot.positionX, robot.positionY, checkDirection(robot.direction)); // print the initial position of the robot, based on the input from the user

        robot = processSimulation(testCaseString, robot); // call the function to process the test case string that was received by the user and update the robots final state

        printf(PRINT_FINAL_ROBOT_COORDINATES, testCaseString, robot.positionX, robot.positionY, checkDirection(robot.direction)); // print the final position of the robot, based on the processed received command from the user

        printf(PRINT_BLOCK_SPACING); // print some spacing block in case of next command round
    } while (runAnotherSimulation()); // iterate until the user does not want to continue inputting further test case commands to the robot

    return 0; // exit the program
}

// Function to read the position from the user for a particular axis
int readPosition(char axis) {
    // Variables declarations
    char *input = calloc(SIZE_USER_INPUT, sizeof(char)); // store the user's input
    int inputNumber; // store the integer representation of the input

    if (strlen(input) == (SIZE_USER_INPUT-1) && input[SIZE_USER_INPUT-1] == '\0' ){ // Check if the input array is full
        clear_stdin(); // call function to clear the buffer
    }

    do {
        printf(PROMPT_USER_STARTING_POSITION, axis); // prompt the user for an input value for the particular axis
        fgets(input, SIZE_USER_INPUT, stdin); // read input from buffer

        if (sscanf(input, "%d", &inputNumber) == 1 && strlen(input) <= 3) { // Read integers from the stored character array
                                                                                   // Check if the input contains an integer value
                                                                                   // Check if the stored character array is not of size 3 (including \n)
            if (inputNumber >= LOWER_POSITION_BOUND && inputNumber <= UPPER_POSITION_BOUND) { // check if the input number is within the accepted bounds
                return inputNumber; // return the value to the user
            } else { // case of the input being out of bounds
                printf(VALUE_OUT_OF_BOUNDS); // notify the user for entering out of bounds number as input
            }
        } else { // handle alphabetical input
            if (input[0] == EXIT_CHAR && strlen(input) == 2) { // check if the EXIT_CHAR has been entered
                printf(EXIT_MESSAGE); // print the exit message
                exit(0); // exit the program
            } else { // handle all the other invalid input
                printf(INVALID_INPUT); // notify the user of invalid input
            }
        }
    } while (TRUE); // keep prompting the user for input
}

// Function to read the set of instructions from the user and return it as a string
char *readSimulationInstruction() {
    // Variables declarations
    char *input = calloc(SIZE_USER_INPUT,sizeof(char)); // Create pointer and allocate memory to store the input from the user
    int i; // index for the loop
    int validCommand; // variable to store whether the given command within the string the user has entered is valid or not

    do {
        validCommand = TRUE; // initialize the value of the variable and set it to true
        printf(PROMPT_FOR_USER_DIRECTIONS); // prompt the user for an instruction set
        fgets(input, SIZE_USER_INPUT, stdin); // read input from buffer

        if (input[0] == '\n') { // check if the input from the user is empty
            printf(INVALID_INPUT_EMPTY_LINE); // notify the user for invalid input
            validCommand = FALSE; // change the value of the validCommand to false since the given command was invalid
            continue; // skip this iteration
        }
        for (i = 0; i < strlen(input); i++) { // iterate through the entered string
            if (input[i] != '\n') { // check if the current character is not the new line char
                if (input[i] != MOVE_FORWARD && input[i] != TURN_90_DEGREES_CLOCKWISE) { // check if the input does not equal either to the move forward instruction or to the turning one
                    printf(INVALID_COMMAND); // notify the user that there was an invalid command found
                    validCommand = FALSE; // alter the value of validCommand to false
                    break; // exit the loop
                }
            }
        }
        if (validCommand){ // check if there was no invalid command found within the entered instruction set by the user
            input[strlen(input)-1] = '\0'; // remove the \n as the last element of the pointer array and insert the null character to represent the end of string
            return input; // return the string as a valid instruction set for the robot
        }
    } while (!validCommand); // keep iterating as long as there has been an invalid command/string found
}

// Function to process the entered instruction set by the user and alter the robot's coordinates accordingly
ROBOT processSimulation(const char *testCaseString, ROBOT robot) {
    int i; // index for the loop

    for (i = 0; i < strlen(testCaseString); i++) { // iterate through the characters of the instruction string
        if (testCaseString[i] == MOVE_FORWARD) { // check if there was detected a "move forward" command
            robot = move(robot); // call the function to move the robot forward and alter the robot's state
        } else if (testCaseString[i] == TURN_90_DEGREES_CLOCKWISE) { // check if there was a "turn" command found
            robot = turn(robot); // call the function to turn the robot clockwise and alter the robot's state
        }
    }
    return robot; // return the robot's state
}

// Function to make the robot move forward
ROBOT move(ROBOT robot) {
    switch (robot.direction) { // switch statement that handles the alteration in robot's position based on it's current direction
        case North: // check if the current direction of the robot is set to North
            robot.positionY++; // increment the value in the Y axis by 1, i.e. move forward towards the North
            break;
        case East: // check if the current direction of the robot is set to East
            robot.positionX++; // increment the value in the X axis by 1, i.e. move forward towards the East
            break;
        case South: // check if the current direction of the robot is set to South
            robot.positionY--; // decrement the value in the Y axis by 1, i.e. move forward towards the South
            break;
        case West: // check if the current direction of the robot is set to West
            robot.positionX--; // decrement the value in the X axis by 1, i.e. move forward towards the West
            break;
    }
    return robot; // return the robot's state
}

// Function to make the robot turn clockwise 90 degrees, to a different orientation of the horizon
ROBOT turn(ROBOT robot) {
    switch (robot.direction) { // switch statement that handles the alteration in robot's direction based on it's current direction
        case North: // check if the current direction of the robot is set to North
            robot.direction = East; // change the direction of the robot to East (turn 90 degrees clockwise)
            break;
        case East: // check if the current direction of the robot is set to East
            robot.direction = South; // change the direction of the robot to South (turn 90 degrees clockwise)
            break;
        case South: // check if the current direction of the robot is set to South
            robot.direction = West; // change the direction of the robot to West (turn 90 degrees clockwise)
            break;
        case West: // check if the current direction of the robot is set to West
            robot.direction = North; // change the direction of the robot to North (turn 90 degrees clockwise)
            break;
    }
    return robot; // return the robot's state
}

// Function to check if the user wants to input another instruction set
int runAnotherSimulation() {
    // Variables declarations
    char input; // store the user's inputChar
    char secondChar; // store second char to check for error

    printf(PROMPT_FOR_ANOTHER_TEST_CASE); // prompt the user with a message asking if they want to play again
    input = getc(stdin); // read user's answer

    if (input == '\n') { // handle enter
        printf(INVALID_INPUT_EMPTY_LINE); // notify the user of invalid inputChar
        return runAnotherSimulation(); // recursive call to prompt the user again for a valid inputChar
    }

    secondChar = getc(stdin); // read second char from buffer
    if (secondChar && secondChar != '\n') { // if there is another char and that char is not a new line
        printf(INVALID_INPUT); // notify the user of invalid inputChar
        clear_stdin(); // call the method to clear the buffer
        return runAnotherSimulation(); // recursive call to prompt the user again for a valid inputChar
    }

    if(input == 'y' || input == 'Y') { // covers the case that the user wants to play again
        return 1;
    }else if(input == 'n' || input == 'N'){ // covers the case that the user does not want to play again
        printf(EXIT_MESSAGE);
        return 0; // return user's response
    } else { // covers the case of invalid inputChar entered by the user
        printf(INVALID_INPUT); // notify the user of invalid inputChar
        return runAnotherSimulation(); // recursive call to prompt the user again for a valid inputChar
    }

}

// Function to clear the stdin buffer
void clear_stdin() {
    while( getchar() != '\n' ); // iterate and empty the buffer until the EOF character is found
}

// Function to correlate the integer representation of the robot's direction based on the enum's value its corresponding representation as cardinal points (i.e. North, East, South, West)
char *checkDirection(int intDirectionRepresentation) {
    char *direction; // pointer to store the char representation of the cardinal point of the robot's direction

    switch (intDirectionRepresentation) { // switch statement that handles correlation check among the integer representation of the cardinal points
        case 0: // check if the enum's direction value equals to 0, meaning it is being set to the North
            direction = "North"; // assign the North string to the pointer
            break;
        case 1: // check if the enum's direction value equals to 0, meaning it is being set to the East
            direction = "East"; // assign the East string to the pointer
            break;
        case 2: // check if the enum's direction value equals to 0, meaning it is being set to the South
            direction = "South"; // assign the South string to the pointer
            break;
        case 3: // check if the enum's direction value equals to 0, meaning it is being set to the West
            direction = "West"; // assign the West string to the pointer
            break;
    }

    return direction; // return the direction's value that is based on the corresponding cardinal point
}