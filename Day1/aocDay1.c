//******************************************************************************
//
//  aocDay1.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day ones challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//******************************************************************************
//
//  Function: aocDay1
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day ones
//               challenge
//
//******************************************************************************
void aocDay1()
{
    // variables for storing the floor and position
    int floor = 0;
    int chPos = 0;
    int position = 0;

    // variable for storing the character from the input file
    char ch;

    // open text file
    FILE *input = fopen("../Day1/input.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file input.txt\n\n");
    }
    else
    {
        // run code to calculate floor
        while ((ch = fgetc(input)) != EOF)
        {
            //increment character position
            chPos++;

            if (ch == '(')
            {
                floor++;
            }
            else if (ch == ')')
            {
                floor--;
            }

            // update position if it is the first time santa entered the basement
            if (position == 0 && floor == -1)
            {
                position = chPos;
            }
        }

        printf("The floor Santa needs to be on is %d\n", floor);
        printf("The position of the character when santa first entered the basement is %d\n\n", position);
    }
    // close text file
    fclose(input);

    // prompt user for input
    char enter;
    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("%c", &enter);

    // re-enter main function
    main();
}