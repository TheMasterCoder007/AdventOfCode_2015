//******************************************************************************
//
//  aocDay6.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day sixes challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//------------------------------------------------------------------------------
//  CONSTANTS AND MACROS
//------------------------------------------------------------------------------

#define MAX_LIGHT_GRID_SIZE     1000

//------------------------------------------------------------------------------
//  TYPEDEFS AND ENUMS
//------------------------------------------------------------------------------

typedef enum
{
    command_toggle  = 0,
    command_off     = 1,
    command_on      = 2
} command;

//------------------------------------------------------------------------------
//  PRIVATE GLOBAL VARIABLES
//------------------------------------------------------------------------------

static bool grid[MAX_LIGHT_GRID_SIZE][MAX_LIGHT_GRID_SIZE];
static uint8_t grid2[MAX_LIGHT_GRID_SIZE][MAX_LIGHT_GRID_SIZE];

//------------------------------------------------------------------------------
//  FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

static void setLights (int cmd, int startX, int startY, int endX, int endY);
static void parseString (char string[]);

//******************************************************************************
//
//  Function: aocDay6
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day sixes
//               challenge
//
//******************************************************************************
void aocDay6()
{
    // variables for storing which lights are on (part 1 and 2)
    int lightsOn = 0;
    int lightsOn2 = 0;

    // variable for storing character from input file
    char ch;

    // initialize array
    for (int i = 0; i < MAX_LIGHT_GRID_SIZE; i++)
        memset(grid[i], false, MAX_LIGHT_GRID_SIZE * sizeof(bool));
    for (int i = 0; i < MAX_LIGHT_GRID_SIZE; i++)
        memset(grid2[i], 0, MAX_LIGHT_GRID_SIZE * sizeof(uint8_t));

    // open text file
    FILE *input = fopen("../Day6/input.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file input.txt\n\n");
    }
    else
    {
        // create local variables used in while loop
        int charCount = 0;
        char tempString[50];
        memset(tempString, '\0', 50 * sizeof(char));

        // parse text file
        while ((ch = fgetc(input)) != EOF)
        {
            if (ch == '\n')
            {
                parseString(tempString);

                // reset temp string
                memset(tempString, '\0', 50 * sizeof(char));
                charCount = 0;
            }
            else
            {
                tempString[charCount] = ch;
                charCount++;
            }
        }

        // check array for lights that are on
        for (int x = 0; x < MAX_LIGHT_GRID_SIZE; x++)
        {
            for (int y = 0; y < MAX_LIGHT_GRID_SIZE; y++)
            {
                if (grid[x][y] == true)
                    lightsOn++;

                if (grid2[x][y] > 0)
                    lightsOn2 += grid2[x][y];
            }
        }

        // give answers
        printf("The number of lights lit for part 1 is %d\n", lightsOn);
        printf("The number of lights lit for part 2 is %d\n", lightsOn2);
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

//******************************************************************************
//
//  Function: setLights
//
//  Arguments: int command, int startX, int startY, int endX, int endY
//
//  Returns: void
//
//  Description: This function is called to set the lights based on the command
//
//******************************************************************************
static void setLights (int cmd, int startX, int startY, int endX, int endY)
{
    for (int x = startX; x <= endX; x++)
    {
        for (int y = startY; y <= endY; y++)
        {
            if (cmd == command_toggle)
            {
                grid[x][y] = !grid[x][y];
                grid2[x][y] += 2;
            }
            else if (cmd == command_on)
            {
                grid[x][y] = true;
                grid2[x][y]++;
            }
            else if (cmd == command_off)
            {
                grid[x][y] = false;

                if (grid2[x][y] > 0)
                    grid2[x][y]--;
            }
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
//******************************************************************************
//
//  Function: parseString
//
//  Arguments: char string[]
//
//  Returns: void
//
//  Description: This function parses the string and extracts the data to
//               shared variables
//
//******************************************************************************
static void parseString (char string[])
{
    char checkString1[] = "toggle";
    char checkString2[] = "on";
    char checkString3[] = "off";
    char *string1;
    char *string2;
    char *string3;
    int cmd;
    int startX;
    int startY;
    int endX;
    int endY;

    // parse command type
    string1 = strstr(string, checkString1);
    string2 = strstr(string, checkString2);
    string3 = strstr(string, checkString3);

    if (string1 != NULL)
        cmd = command_toggle;
    else if (string2 != NULL)
        cmd = command_on;
    else if (string3 != NULL)
        cmd  = command_off;
    else
        exit(6);

    // extract integers
    sscanf(string,"%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d",
           &startX, &startY, &endX, &endY);

    // set lights
    setLights(cmd, startX, startY, endX, endY);
}
#pragma clang diagnostic pop