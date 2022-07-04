//
// Created by CoryLamming on 2022-06-28.
//

#include "AdventOfCode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// defines
#define TRUE    1
#define FALSE   0
#define __packed 			__attribute__((__packed__))

typedef struct __packed{
    short pos_x:16;
    short pos_y:16;
} coordinates;

// declare private variables here
static short houses = 1; // start location counts
static int ch;
static char enter;

    void aocDay3()
    {
        // open text file
        FILE *input = fopen("Input_Files/Input_3.txt", "r");

        // check for problem reading file
        if (input == NULL)
        {
            printf("There was a problem opening the file Input_3.txt\n\n");
        }
        else
        {
            int count = 1;

            // find the amount of characters in file
            while ((ch = fgetc(input)) != EOF)
            {
                count++;
            }
            rewind(input);

            // initialize dynamic array to store stop locations
            int *stopLocations = malloc(sizeof(coordinates) * count);
            memset(stopLocations, 0, count * sizeof(coordinates));

            int x = 0;
            int y = 0;
            int arrayLoc = 1;


            while ((ch = fgetc(input)) != EOF)
            {
                if (ch == '^')
                {
                    y++;
                }
                else if (ch == 'v')
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

                {
                    coordinates position;
                    position.pos_x = x;
                    position.pos_y = y;

                    stopLocations[arrayLoc] = position;
                }

                arrayLoc++;
            }

            // process data to find number of houses stopped at
            unsigned char increase;

            for (int i = 0; i < count; i++)
            {
                if (i == 0)
                {
                    increase = TRUE; // first move counts
                }
                for (int j = 0; j < i; j++)
                {
                    if (stopLocations[i] == stopLocations[j])
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