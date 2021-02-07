/* ====================================
File name: exerc_X_X.c
Date: 2020-XX-XX
Group nr 14
Members that contribute to the solutions Krasen Parvanov, Chrysostomos Tsagkidis, Eemil Jeskanen
Member not present at demonstration time: N/A
Demonstration code: [<Ass code 1-4> <abc>]
====================================== */

// Include section
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Define section
#define X_AXIS 'x' // string to specify the "x" axis in the coordinate system
#define Y_AXIS 'y' // string to specify the "y" axis in the coordinate system
#define PROMPT_USER_STARTING_POSITION "Please enter the starting position for the robot:\n %c axis: " // string to ask for the starting position for a specific axis from the user
#define SIZE_USER_INPUT 50 // Used to set the size of the array for the user's input
#define INVALID_INPUT "Not valid, please try again \n" // Invalid input prompt
#define EXIT_CHAR 'q' // Character for exiting the program
#define EXIT_MESSAGE "Exiting the program...\n" // String to be printed when exiting the program
#define LOWER_POSITION_BOUND 0 // Lower accepted value for the position in the coordinates system
#define UPPER_POSITION_BOUND 99 // Upper accepted value for the position in the coordinates system
#define VALUE_OUT_OF_BOUNDS "You entered a value that is invalid as for the coordinates. Please enter a value between 0-99 next time!\n"
#define INVALID_COMMAND "You have entered an invalid command as for the robot to follow. Please enter a string that contains only \"m\" and/or \"t\" values for the command!\n"
#define PROMPT_FOR_USER_DIRECTIONS "Please enter a command for the robot to follow! Type \"m\" for moving towards the current direction or \"t\" to turn 90 degrees clockwise!\n"
#define INVALID_INPUT_EMPTY_LINE "A simple [enter] is not a valid input! Please try again!\n"
#define MOVE_FORWARD 'm'
#define TURN_90_DEGREES_CLOCKWISE 't'
#define PROMPT_FOR_ANOTHER_TEST_CASE "\nDo you want to execute another test case? (Y/N)\n"
#define PRINT_INITIAL_ROBOT_COORDINATES "\nInitial position of the robot:\nX: %d, Y: %d, Direction: %s\n"
#define PRINT_FINAL_ROBOT_COORDINATES "Final position after receiving the command \"%s\":\nX: %d, Y: %d, Direction: %s\n"
#define PRINT_BLOCK_SPACING "\n=====================================================\n"
#define TRUE 1
#define FALSE 0

/* ==================================== Main program section ====================================== */
/*
 *
 */

enum DIRECTION {North , East, South, West};

typedef struct{
    int positionX;
    int positionY;
    enum DIRECTION direction;
}ROBOT;

ROBOT move(ROBOT robot);
ROBOT turn(ROBOT robot);
int getPosition(char axis);
char *getTestCaseDirections();
ROBOT processTestCase(const char *testCaseString, ROBOT robot);
int runAnotherTestCase();
void clear_stdin();
char *checkDirection(int intDirectionRepresentation);

int main() {
    // Variable declarations
    ROBOT robot;
    robot.direction = North;
    char *testCaseString = calloc(SIZE_USER_INPUT,sizeof(char));

    do {
        robot.positionX = getPosition(X_AXIS);
        robot.positionY = getPosition(Y_AXIS);

        testCaseString = getTestCaseDirections();

        printf(PRINT_INITIAL_ROBOT_COORDINATES, robot.positionX, robot.positionY, checkDirection(robot.direction));

        robot = processTestCase(testCaseString, robot);

        printf(PRINT_FINAL_ROBOT_COORDINATES, testCaseString, robot.positionX, robot.positionY, checkDirection(robot.direction));

        printf(PRINT_BLOCK_SPACING);
    } while (runAnotherTestCase());

    return 0;
}

int getPosition(char axis) {
    // Variables declarations
    char *input = calloc(SIZE_USER_INPUT, sizeof(char)); // store the user's input
    int inputNumber; // store the integer representation of the input

    if (strlen(input) == (SIZE_USER_INPUT-1) && input[SIZE_USER_INPUT-1] == '\0' ){ // Check if the input array is full
        clear_stdin(); // call function to clear the buffer
    }

    do {
        printf(PROMPT_USER_STARTING_POSITION, axis);
        fgets(input, SIZE_USER_INPUT, stdin); // read input from buffer

        if (sscanf(input, "%d", &inputNumber) == 1 && strlen(input) <= 3) {
            if (inputNumber >= LOWER_POSITION_BOUND && inputNumber <= UPPER_POSITION_BOUND) {
                return inputNumber;
            } else {
                printf(VALUE_OUT_OF_BOUNDS);
            }
        } else {
            if (input[0] == EXIT_CHAR && strlen(input) == 2) { // check if the EXIT_CHAR has been entered
                printf(EXIT_MESSAGE); // print the exit message
                exit(0); // exit the program
            } else { // handle all the other invalid input
                printf(INVALID_INPUT); // notify the user of invalid input
            }
        }
    } while (TRUE); // keep prompting the user for input
}

char *getTestCaseDirections() {
    // Variables declarations
    char *input = calloc(SIZE_USER_INPUT,sizeof(char));
    int i;
    int validCommand;

    do {
        validCommand = TRUE;
        printf(PROMPT_FOR_USER_DIRECTIONS);
        fgets(input, SIZE_USER_INPUT, stdin); // read input from buffer

        if (input[0] == '\n') {
            printf(INVALID_INPUT_EMPTY_LINE);
            validCommand = FALSE;
            continue;
        }
        for (i = 0; i < strlen(input); i++) {
            if (input[i] != '\n') {
                if (input[i] != MOVE_FORWARD && input[i] != TURN_90_DEGREES_CLOCKWISE) {
                    printf(INVALID_COMMAND);
                    validCommand = FALSE;
                    break;
                }
            }
        }
        if (validCommand == TRUE){
            input[strlen(input)-1] = '\0'; // remove the \n as the last element of the pointer array and insert the null character to represent the end of string
            return input;
        }
    } while (!validCommand);
}

ROBOT processTestCase(const char *testCaseString, ROBOT robot) {
    int i;

    for (i = 0; i < strlen(testCaseString); i++) {
        if (testCaseString[i] == MOVE_FORWARD) {
            robot = move(robot);
        } else if (testCaseString[i] == TURN_90_DEGREES_CLOCKWISE) {
            robot = turn(robot);
        }
    }
    return robot;
}

ROBOT move(ROBOT robot) {
    switch (robot.direction) {
        case North:
            robot.positionY++;
            break;
        case East:
            robot.positionX++;
            break;
        case South:
            robot.positionY--;
            break;
        case West:
            robot.positionX--;
            break;
    }
    return robot;
}

ROBOT turn(ROBOT robot) {
    switch (robot.direction) {
        case North:
            robot.direction = East;
            break;
        case East:
            robot.direction = South;
            break;
        case South:
            robot.direction = West;
            break;
        case West:
            robot.direction = North;
            break;
    }
    return robot;
}

int runAnotherTestCase() {
    // Variables declarations
    char input; // store the user's inputChar
    char secondChar; // store second char to check for error

    printf(PROMPT_FOR_ANOTHER_TEST_CASE); // prompt the user with a message asking if they want to play again
    input = getc(stdin); // read user's answer

    if (input == '\n') { // handle enter
        printf(INVALID_INPUT_EMPTY_LINE); // notify the user of invalid inputChar
        return runAnotherTestCase(); // recursive call to prompt the user again for a valid inputChar
    }

    secondChar = getc(stdin); // read second char from buffer
    if (secondChar && secondChar != '\n') { // if there is another char and that char is not a new line
        printf(INVALID_INPUT); // notify the user of invalid inputChar
        clear_stdin(); // call the method to clear the buffer
        return runAnotherTestCase(); // recursive call to prompt the user again for a valid inputChar
    }

    if(input == 'y' || input == 'Y') { // covers the case that the user wants to play again
        return 1;
    }else if(input == 'n' || input == 'N'){ // covers the case that the user does not want to play again
        printf(EXIT_MESSAGE);
        return 0; // return user's response
    } else { // covers the case of invalid inputChar entered by the user
        printf(INVALID_INPUT); // notify the user of invalid inputChar
        return runAnotherTestCase(); // recursive call to prompt the user again for a valid inputChar
    }

}

void clear_stdin() {
    while( getchar() != '\n' ); // iterate and empty the buffer until the EOF character is found
}

char *checkDirection(int intDirectionRepresentation) {
    char *direction;

    switch (intDirectionRepresentation) {
        case 0:
            direction = "North";
            break;
        case 1:
            direction = "East";
            break;
        case 2:
            direction = "South";
            break;
        case 3:
            direction = "West";
            break;
    }

    return direction;
}