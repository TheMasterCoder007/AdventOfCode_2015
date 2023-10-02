//******************************************************************************
//
//  AdventOfCode.h:
//
//	Software developed by TheMasterCoder007 (Cory Lamming)
//	for skill development and entertainment. (2023)
//
//  Header file that contains all global includes, constants, macros,
//  variables, and function declarations for this project.
//
//******************************************************************************

#ifndef ADVENTOFCODE_H
#define ADVENTOFCODE_H

// includes
#include "Day4/md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

// exit codes
#define EXIT_SUCCESSFUL_OPERATION   0
#define EXIT_PROBLEM_OPENING_FILE   1
#define EXIT_MEMORY_ALLOC_ERROR     2
#define EXIT_THREAD_CREATE_FAILED   3
#define EXIT_MUTEX_INIT_FAILED      4
#define EXIT_INVALID_INPUT          5

// declare functions
int main();
void aocDay1();
void aocDay2();
void aocDay3();
void aocDay4();
void aocDay5();
void aocDay6();

#endif //ADVENTOFCODE_H
