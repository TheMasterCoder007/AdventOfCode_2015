//******************************************************************************
//
//  aocDay2.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day twos challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//------------------------------------------------------------------------------
//  CONSTANTS AND MACROS
//------------------------------------------------------------------------------

#define MAX_LINES   1000

//******************************************************************************
//
//  Function: aocDay2
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day twos
//               challenge
//
//******************************************************************************
void aocDay2()
{
    // variables for storing packaging instructions and requirements
    int line = 0;
    int length[MAX_LINES];
    int width[MAX_LINES];
    int height[MAX_LINES];
    int totalSqFt = 0;
    int totalRibbon = 0;

    // open input file
    FILE *input = fopen("../Day2/input.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file input.txt\n\n");
    }
    else
    {
        // import data from text file and store in variable arrays
        while ((fscanf(input, "%dx%dx%d\n", &length[line], &width[line], &height[line])) != EOF)
        {
            line++;
        }
    }
    // close text file
    fclose(input);

    // process data
    for (int lineNum = 0; lineNum < MAX_LINES; lineNum++)
    {
        // calculate square feet for three different sides
        int sideOne     = length[lineNum] * width[lineNum];
        int sideTwo     = width[lineNum] * height[lineNum];
        int sideThree   = height[lineNum] * length[lineNum];

        // find the smallest side
        int smallSide   = INT_MAX;

        if (sideOne < smallSide)
        {
            smallSide = sideOne;
        }
        if (sideTwo < smallSide)
        {
            smallSide = sideTwo;
        }
        if (sideThree < smallSide)
        {
            smallSide = sideThree;
        }

        // find the two smallest sides for calculating ribbon needed
        int smallSideOne = length[lineNum];
        int smallSideTwo;

        if (width[lineNum] < smallSideOne)
        {
            smallSideOne = width[lineNum];
            smallSideTwo = length[lineNum];
        }
        else
        {
            smallSideTwo = width[lineNum];
        }

        if (height[lineNum] < smallSideOne)
        {
            smallSideTwo = smallSideOne;
            smallSideOne = height[lineNum];
        }
        else if (height[lineNum] < smallSideTwo)
        {
            smallSideTwo = height[lineNum];
        }

        // calculate total square feet needed + extra
        totalSqFt += ((2 * sideOne) + (2 * sideTwo) + (2 * sideThree) + smallSide);

        // calculate total ribbon needed for bow and present wrap
        totalRibbon += ((length[lineNum] * width[lineNum] * height[lineNum]) + (smallSideOne + smallSideOne + smallSideTwo + smallSideTwo));
    }

    // give answer
    printf("The total square feet of wrapping paper needed is %d\n", totalSqFt);
    printf("The total length of ribbon needed is %d\n\n", totalRibbon);

    // prompt user for input
    char enter;
    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("%c", &enter);

    // re-enter main function
    main();
}