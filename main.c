#include <stdio.h>

int main()
{
    // define functions
    int aocDay1();

    // call function to run (based on day). comment out functions that are not needed.
    aocDay1();

    return 0;
}

int aocDay1()
{

    // variables
static int floor = 0;
static char ch;

    // open text file
    FILE *input = fopen("Input_1.txt", "r");

    // check for problem reading file
    if (input == NULL)
    {
        printf("There was a problem opening the file");
        return 1;
    }

    // run code to calculate floor
    while ((ch = fgetc(input)) != EOF)
    {
        if (ch == '(')
        {
            floor++;
        }
        else if (ch == ')')
        {
            floor--;
        }
    }

    printf("The floor Santa needs to be on is %d", floor);
    return 0;
}
