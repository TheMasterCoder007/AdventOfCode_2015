//******************************************************************************
//
//  aocDay3.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day threes challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//------------------------------------------------------------------------------
//  CONSTANTS AND MACROS
//------------------------------------------------------------------------------

#define TRUE        1
#define FALSE       0
#define SANTA       1
#define ROBO_SANTA  2

//------------------------------------------------------------------------------
//  TYPEDEFS AND ENUMS
//------------------------------------------------------------------------------

typedef struct {
    // part 1
    short pos_x;
    short pos_y;
    // part 2
    short pos_x1;
    short pos_x2;
    short pos_y1;
    short pos_y2;
} coordinates;

//******************************************************************************
//
//  Function: aocDay3
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day threes
//               challenge
//
//******************************************************************************
void aocDay3()
{
    // variables for storing houses visited (part 1 and 2)
    short houses     = 1; // start location counts
    short houses_p2  = 1; // start location counts

    // variable for storing character from input file
    char ch;

    // open text file
    FILE *input = fopen("../Day3/input.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file input.txt\n\n");
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
        coordinates *stopLocations = malloc(sizeof(coordinates) * count);
        memset(stopLocations, 0, count * sizeof(coordinates));

        // part 1
        short x     = 0;
        short y     = 0;
        //part 2
        short x1    = 0;
        short x2    = 0;
        short y1    = 0;
        short y2    = 0;

        unsigned short arrayLoc = 1;
        unsigned char santa     = SANTA;

        // process input data
        while ((ch = fgetc(input)) != EOF)
        {
            if (ch == '^')
            {
                y++;

                if (santa == SANTA)
                    y1++;
                else
                    y2++;
            }
            else if (ch == 'v')
            {
                y--;

                if (santa == SANTA)
                    y1--;
                else
                    y2--;
            }
            else if (ch == '>')
            {
                x++;

                if (santa == SANTA)
                    x1++;
                else
                    x2++;
            }
            else if (ch == '<')
            {
                x--;

                if (santa == SANTA)
                    x1--;
                else
                    x2--;
            }

            // copy position data into struct
            {
                coordinates position;
                position.pos_x  = x;
                position.pos_y  = y;
                position.pos_x1 = x1;
                position.pos_x2 = x2;
                position.pos_y1 = y1;
                position.pos_y2 = y2;

                stopLocations[arrayLoc] = position;
            }

            arrayLoc++;
            santa = (santa == SANTA ? ROBO_SANTA : SANTA);
        }

        // process data to find number of houses stopped at
        unsigned char increase;
        unsigned char increase1;
        unsigned char increase2;

        for (int i = 0; i < count; i++)
        {
            if (i == 0)
            {
                increase = FALSE;
                increase1 = FALSE;
                increase2 = FALSE;
            }
            else
            {
                increase = TRUE;
                increase1 = TRUE;
                increase2 = TRUE;
            }

            for (int j = 0; j < i; j++)
            {
                // part 1
                if (stopLocations[i].pos_x == stopLocations[j].pos_x && stopLocations[i].pos_y == stopLocations[j].pos_y)
                    increase = FALSE;

                // part 2
                if ((stopLocations[i].pos_x1 == stopLocations[j].pos_x1 && stopLocations[i].pos_y1 == stopLocations[j].pos_y1)
                        || (stopLocations[i].pos_x1 == stopLocations[j].pos_x2 && stopLocations[i].pos_y1 == stopLocations[j].pos_y2))
                    increase1 = FALSE;

                if ((stopLocations[i].pos_x2 == stopLocations[j].pos_x2 && stopLocations[i].pos_y2 == stopLocations[j].pos_y2)
                    || (stopLocations[i].pos_x2 == stopLocations[j].pos_x1 && stopLocations[i].pos_y2 == stopLocations[j].pos_y1))
                    increase2 = FALSE;
            }

            // increase house count variables
            if (increase == TRUE)
                houses++;

            if (increase1 == TRUE && increase2 == TRUE)
                houses_p2 += 2;
            else if (increase1 == TRUE || increase2 == TRUE)
                houses_p2++;
        }

        // free memory
        free (stopLocations);
    }
    // close text file
    fclose(input);

    // give answers
    printf("The amount of houses Santa visited is %d houses.\n", houses);
    printf("The amount of houses both Santa's visited is %d houses.\n\n", houses_p2);

    // prompt user for input
    char enter;
    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("%c", &enter);

    // re-enter main function
    main();
}