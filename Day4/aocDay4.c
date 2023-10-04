//******************************************************************************
//
//  aocDay4.c:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Source file that contains all code related to day fours challenge.
//
//******************************************************************************

//------------------------------------------------------------------------------
//  INCLUDES
//------------------------------------------------------------------------------

#include "../AdventOfCode.h"

//------------------------------------------------------------------------------
//  CONSTANTS AND MACROS
//------------------------------------------------------------------------------

// clock macro
#define TIME_IN_SECONDS(clocks)     (double)((double)(clocks) / CLOCKS_PER_SEC)

// thread gap constants
#define THREAD_ITERATIONS_GAP   (INT_MAX / 1024)
#define THREAD_ITERATIONS_TH1   (THREAD_ITERATIONS_GAP)
#define THREAD_ITERATIONS_TH2   (THREAD_ITERATIONS_GAP * 2)
#define THREAD_ITERATIONS_TH3   (THREAD_ITERATIONS_GAP * 3)
#define THREAD_ITERATIONS_TH4   (THREAD_ITERATIONS_GAP * 4)
#define THREAD_ITERATIONS_TH5   (THREAD_ITERATIONS_GAP * 5)
#define THREAD_ITERATIONS_TH6   (THREAD_ITERATIONS_GAP * 6)
#define THREAD_ITERATIONS_TH7   (THREAD_ITERATIONS_GAP * 7)
#define THREAD_ITERATIONS_TH8   (THREAD_ITERATIONS_GAP * 8)

// number of threads
#define MAX_THREADS 8

//------------------------------------------------------------------------------
//  FUNCTION PROTOTYPES
//------------------------------------------------------------------------------

static int coinHashCheck(const uint8_t *result);
static int MD5main(char argv[]);
static void *threadHash (void *thread_arg);

//------------------------------------------------------------------------------
//  PRIVATE GLOBAL VARIABLES
//------------------------------------------------------------------------------

// coin inputs
static int adventCoinInput  = 0;
static int adventCoinInput2 = 0;

// mutexes for protecting shared variables
pthread_mutex_t coinInputMutex = PTHREAD_MUTEX_INITIALIZER;

//******************************************************************************
//
//  Function: coinHashCheck
//
//  Arguments: pointer to hash result
//
//  Returns: int
//
//  Description: This function checks the hash result and compares it to the
//               requirements for the advent coin answer. Zero is returned when
//               no match was found. One is returned when the hash matches the
//               requirements for the answer on part one. Two is returned when
//               the hash matches the requirements for the answer on part two.
//
//******************************************************************************
static int coinHashCheck(const uint8_t *result)
{
    typedef struct __attribute__((__packed__))
    {
        uint8_t lowerNibble:4;
        uint8_t upperNibble:4;
    } hashResult;

    // checks 16 bytes of result
    for (unsigned char byte = 0; byte < 16; byte++)
    {
        uint8_t data = result[byte];
        hashResult *results = (hashResult *)&data;

        // The first 5 nibbles of the result need to be 0.
        // The first statement checks that the first 4 nibbles are 0.
        // If true, it continues to check the 5th and 6th nibbles.
        // If this is false, it returns 0 indicating a incorrect match
        if (byte < 2 && results->upperNibble == 0 && results->lowerNibble == 0)
            continue;
        // This statement checks that the 5th nibble is 0 and the 6th is a non zero value
        // If this this true, it returns 1 which indicates a match for part one
        else if (byte == 2 && results->upperNibble == 0 && results->lowerNibble != 0)
            return 1;
        // This statement checks that the 5th and 6th nibble are 0.
        // If this is true, it returns 2 indicating a match for part two
        else if (byte == 2 && results->upperNibble == 0 && results->lowerNibble == 0)
            return 2;
        // Incorrect match.
        else
            return 0;
    }

    // should never get here, but all control paths have to have a return value
    return 0;
}

//******************************************************************************
//
//  Function: MD5main
//
//  Arguments: char argv[]
//
//  Returns: int
//
//  Description: This function runs the MD5 hash using the string that is input
//               into this function. The coinHashCheck function is then called
//               to compare the hash to the answer requirements. The results
//               of the coinHashCheck are then returned.
//
//******************************************************************************
static int MD5main(char argv[])
{
    uint8_t *result;
    int resultMatch;

    // runs md5 algorithm and gets pointer to result
    result = md5String(&argv[0]);

    // runs result through the coin hash check to see if it is a match
    resultMatch = coinHashCheck(result);

    // free dynamic memory
    free(result);

    // returns match results
    return resultMatch;
}

//******************************************************************************
//
//  Function: threadHash
//
//  Arguments: void * to thread number
//
//  Returns: void *
//
//  Description: This function iterates through the block given and attempts to
//               get the advent coin solve. For each loop, the iteration number
//               is added to the secret key. This new string is then passed into
//               the md5 hash and checked against the requirements of the solve.
//               Once the answer for both parts has been solved, all threads are
//               killed.
//
//******************************************************************************
static void *threadHash (void *thread_arg)
{
    // array to store thread iteration values
    int threadIterations[MAX_THREADS] =
    {
        THREAD_ITERATIONS_TH1,
        THREAD_ITERATIONS_TH2,
        THREAD_ITERATIONS_TH3,
        THREAD_ITERATIONS_TH4,
        THREAD_ITERATIONS_TH5,
        THREAD_ITERATIONS_TH6,
        THREAD_ITERATIONS_TH7,
        THREAD_ITERATIONS_TH8
    };

    int thread = *((int*)thread_arg);

    // The range blocks are broken down into smaller blocks to increase the efficiency of multi-thread use.
    // This allows the code to cover the whole range of INT_MAX while still making use of multiple threads
    // on smaller value solves.
    for (int block = 1; block <= 128; block++)
    {
        int startLoop = ((threadIterations[thread] * block) - THREAD_ITERATIONS_GAP);
        char secretKey[255];

        // INT_MAX does not divide to a whole number.
        // Use INT_MAX if it ever gets to loop 128 and thread is 7
        if (thread == 7 && block == 128)
            threadIterations[thread] = INT_MAX;

        // solve hash
        for (int number = startLoop; number < threadIterations[thread]; number++)
        {
            sprintf(secretKey, "yzbqklnj%d", number);
            int hashResult = MD5main(secretKey);

            // mutex variables to create thread safe environment
            pthread_mutex_lock(&coinInputMutex);

            // hash match found for part 1 of the challenge
            if (hashResult == 1)
            {
                // first modification of the input answer
                // or lower answer found by another thread
                // (challenge requires lowest number that creates a solve)
                if (adventCoinInput == 0 || number < adventCoinInput)
                {
                    // update coin input and print answer
                    adventCoinInput = number;
                    printf("Thread %d found the answer at loop %d. (Part 1)\n", thread, number);
                }
            }
            // hash solved for part two of the challenge
            else if (hashResult == 2)
            {
                // update coin input and print answer
                adventCoinInput2 = number;
                printf("Thread %d found the answer at loop %d. (Part 2)\n", thread, number);

                // release variables for use by other threads
                pthread_mutex_unlock(&coinInputMutex); // Release the lock on coinInput

                // kill thread
                return NULL;
            }
            // another thread has solved the hash for part two, kill this thread
            else if (adventCoinInput2 != 0) // another thread has already solved the hash
            {
                // release variables for use by other threads
                pthread_mutex_unlock(&coinInputMutex); // Release the lock on coinInput

                // kill thread
                return NULL;
            }

            // release variables for use by other threads
            pthread_mutex_unlock(&coinInputMutex); // Release the lock on coinInput
        }
    }

    // if no solve is found by this thread, kill this thread
    return NULL;
}

//******************************************************************************
//
//  Function: aocDay4
//
//  Arguments: none
//
//  Returns: void
//
//  Description: This function is called to get the solve for day fours
//               challenge
//
//******************************************************************************
void aocDay4()
{
    // set up clock
    clock_t clockStart, clockEnd;
    // get clock tick at start
    clockStart = clock();

    // initialize the mutexes
    if (pthread_mutex_init(&coinInputMutex, NULL) != 0)
    {
        perror("Mutex initialization failed");
        exit(EXIT_MUTEX_INIT_FAILED);
    }

    // array to store thread IDs
    pthread_t threads[MAX_THREADS];

    // create threads
    for (int thread = 0; thread < MAX_THREADS; thread++)
    {
        // allocate memory for thread argument
        int* thread_arg = malloc(sizeof(int));
        if (thread_arg == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_MEMORY_ALLOC_ERROR);
        }

        // set the thread argument to the thread number
        *thread_arg = thread;

        if ((pthread_create(&threads[thread], NULL, threadHash, thread_arg) != 0))
        {
            perror("Thread creation failed");
            exit(EXIT_THREAD_CREATE_FAILED);
        }
    }

    // wait for threads to finish
    for (int thread = 0; thread < MAX_THREADS; thread++)
    {
        pthread_join(threads[thread], NULL);
    }

    // destroy the mutex
    pthread_mutex_destroy(&coinInputMutex);

    // get clock tick at finish
    clockEnd = clock();
    double hashTime = TIME_IN_SECONDS((clockEnd - clockStart));

    // give answers
    printf("\n");
    printf("The coin key for part 1 is %d\n", adventCoinInput);
    printf("The coin key for part 2 is %d\n", adventCoinInput2);
    printf("Hash took %lf seconds.\n\n",hashTime);

    // prompt user for input
    char enter;
    printf("Please press enter to continue...");
    fflush(stdin);
    scanf("%c", &enter);

    // re-enter main function
    main();
}
