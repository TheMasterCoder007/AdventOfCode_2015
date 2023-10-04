//******************************************************************************
//
//  aocDay5.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day fives challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//------------------------------------------------------------------------------
//  CONSTANTS AND MACROS
//------------------------------------------------------------------------------

#define STRING_SIZE         16
#define MAX_PAIR_1_CHECK    13
#define MAX_PAIR_2_CHECK    (STRING_SIZE - 1)

//******************************************************************************
//
//  Function: aocDay5
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day fives
//               challenge
//
//******************************************************************************
void aocDay5()
{
    // variables for storing nice strings (part 1 and 2)
    int niceStrings;
    int niceStrings2;

    // variable for storing character from input file
    char ch;

    // open text file
    FILE *input = fopen("../Day5/input.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file input.txt\n\n");
    }
    else
    {
        // create local variables used in while loop
        niceStrings         = 0;
        niceStrings2        = 0;
        int count           = 1;
        int numVowels       = 0;
        bool doubleLetter   = false;
        bool doubleLetter2 = false;
        bool doublePair     = false;
        bool foundNaughty   = false;
        char prevLetter     = '\n';
        char prevLetter2    = '\n';
        char lineString[STRING_SIZE];

        // run code to calculate naughty and nice strings
        while ((ch = fgetc(input)) != EOF)
        {

            // reset at new line
            if (ch == '\n')
            {
                // check if dual pairs exist
                for (int pair1 = 0; pair1 < MAX_PAIR_1_CHECK; pair1++)
                {
                    char letter1Pair1 = lineString[pair1];
                    char letter2Pair1 = lineString[pair1 + 1];

                    for (int pair2 = pair1 + 2; pair2 < MAX_PAIR_2_CHECK; pair2++)
                    {
                        char letter1Pair2 = lineString[pair2];
                        char letter2Pair2 = lineString[pair2 + 1];

                        if (letter1Pair1 == letter1Pair2 && letter2Pair1 == letter2Pair2)
                        {
                            doublePair = true;
                            break;
                        }
                    }
                }

                // check if the string is nice
                if (numVowels >= 3 && doubleLetter && !foundNaughty)
                    niceStrings++;

                if (doubleLetter2 && doublePair)
                    niceStrings2++;


                // reset variables
                foundNaughty    = false;
                doubleLetter    = false;
                doubleLetter2   = false;
                doublePair      = false;
                numVowels       = 0;
                count           = 1;
                continue;
            }
            // first letter in line
            else if (count == 1)
            {
                prevLetter = ch;
                lineString[count - 1] = ch;

                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                    numVowels++;
            }
            // process the rest of the line
            else
            {
                lineString[count - 1] = ch;

                // part one
                if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                    numVowels++;

                if (ch == prevLetter)
                    doubleLetter = true;

                if ((ch == 'b' && prevLetter == 'a') || (ch == 'd' && prevLetter == 'c')
                            || (ch == 'q' && prevLetter == 'p') || (ch == 'y' && prevLetter == 'x'))
                {
                    foundNaughty = true;
                }

                // part 2
                if (count > 2 && ch == prevLetter2)
                    doubleLetter2 = true;

                // set previous letters
                if (count > 1)
                    prevLetter2 = prevLetter;

                prevLetter = ch;
            }
                count++;
        }

        // give answers
        printf("The number of nice strings for part 1 is %d\n", niceStrings);
        printf("The number of nice strings for part 2 is %d\n", niceStrings2);
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
