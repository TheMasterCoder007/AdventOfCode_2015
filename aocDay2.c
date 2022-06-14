//
// Created by CoryLamming on 2022-06-12.
//

#include "AdventOfCode.h"
#include <limits.h>
#include <stdio.h>

#define MAX_LINES   1000

void aocDay2()
{
    // variables
    static int enter;
    static int line = 0;
    static int length[MAX_LINES];
    static int width[MAX_LINES];
    static int height[MAX_LINES];
    static int totalSqFt = 0;
    static int totalRibbon = 0;

    // open input file
    FILE *input = fopen("Input_Files/Input_2.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file Input_2.txt\n\n");
    }
    else // save data to memory
    {
        // run code to calculate wrapping paper needed
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

    // end function and wait for user input to return to main
    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("&d", &enter);

    // re-enter main function
    main();
}