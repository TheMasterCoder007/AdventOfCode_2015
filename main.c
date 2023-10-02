//******************************************************************************
//
//  main.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains the main loop which is called when the program
//  is run. This loop is also called at the end of each day so you can
//  request the answer for another day
//
//******************************************************************************

#include "AdventOfCode.h"

int main()
{
    // variables
    static int command;
    static char ch;

    // display list of valid commands
    FILE *commandList = fopen("../ListOfCommands.txt", "r");

    if (commandList == NULL)
    {
        printf("There was a problem opening the command list");
        return EXIT_PROBLEM_OPENING_FILE;
    }

    while ((ch = fgetc(commandList)) != EOF)
    {
        putchar(ch);
    }
    fclose(commandList);

    // ask for user input
    printf("Please enter your request: ");
    scanf("%d", &command);

    // process user input
    switch (command)
    {
        case 1:
            aocDay1();
            break;
        case 2:
            aocDay2();
            break;
        case 3:
            aocDay3();
            break;
        case 4:
            aocDay4();
            break;
        case 5:
            aocDay5();
            break;
        case 6:
            aocDay6();
            break;

        default:
            printf("The command is invalid");
            return EXIT_INVALID_INPUT;
    }

    return EXIT_SUCCESSFUL_OPERATION;
}
