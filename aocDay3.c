//
// Created by CoryLamming on 2022-06-28.
//

#include "AdventOfCode.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

void aocDay3()
{
    // variables
    static int houses = 1; // start location counts
    static char ch;
    static int enter;

    // open text file
    FILE *input = fopen("Input_Files/Input_3.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file Input_3.txt\n\n");
    }
    else
    {
        int count = 0;

        // find the amount of characters in file
        while ((ch = fgetc(input)) != EOF)
        {
            count++;
        }

        // initialize dynamic array to store stop locations
        int** stopLocations = malloc(sizeof(int*) * count);
        for (int i = 0; i < count; i++)
        {
            stopLocations[i] = malloc(sizeof(int) * 2);
        }
        int x = 0;
        int y = 0;
        int arrayLoc = 0;

        while ((ch = fgetc(input)) != EOF)
        {
            if (ch == '^')
            {
                y++;
            }
            else if (ch == 'V')
            {
                y--;
            }
            else if (ch == '>')
            {
                x++;
            }
            else if (ch == '<')
            {
                x--;
            }

            stopLocations[arrayLoc][0] = x;
            stopLocations[arrayLoc][1] = y;

            arrayLoc++;
        }

        // process data to find number of houses stopped at
        short increase;

        for (int i = 0; i < count; i++)
        {
            for (int x = 0; x < i; x++)
            {
                if (stopLocations[i][0] == stopLocations[x][0] && stopLocations[i][1] == stopLocations[x][1])
                {
                    increase = FALSE;
                    break;
                }

                increase = TRUE;
            }

            if (increase == TRUE)
                houses++;
        }

        // free memory
        for (int i = 0; i < count; i++)
        {
            free(stopLocations[i]);
        }
        free (stopLocations);
    }
    // close text file
    fclose(input);

    // answers
    printf("The amount of houses Santa visited is %d houses.\n\n", houses);

    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("&d", &enter);

    // re-enter main function
    main();
}