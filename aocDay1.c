//
// Created by CoryLamming on 2022-06-12.
//

#include "AdventOfCode.h"
#include <stdio.h>

void aocDay1()
{
    // variables
    static int floor = 0;
    static int chPos = 0;
    static int position = 0;
    static char ch;
    static int enter;

    // open text file
    FILE *input = fopen("Input_Files/Input_1.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file Input_1.txt\n\n");
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

    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("&d", &enter);

    // re-enter main function
    main();
}