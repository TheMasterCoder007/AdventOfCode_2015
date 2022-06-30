//
// Created by themastercoder007 on 2022-06-10.
//

#include "AdventOfCode.h"
#include <stdio.h>

int main()
{
    // variables
    static int command;
    static char ch;

    // display list of valid commands
    FILE *commandList = fopen("Input_Files/ListOfCommands.txt", "r");

    if (commandList == NULL)
    {
        printf("There was a problem opening the command list");
        return 2;
    }

    while ((ch = fgetc(commandList)) != EOF)
    {
        putchar(ch);
    }
    fclose(commandList);

    // ask for user input
    printf("Please select a command: ");
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

        default:
            printf("The code for the day selected is incomplete or the command is invalid");
            return 1;
    }

    return 0;
}
