cmake_minimum_required(VERSION 3.22)
project(AdventOfCode_2015 C)

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(AdventOfCode_2015
        main.c
        AdventOfCode.h
        Day1/aocDay1.c
        Day2/aocDay2.c
        Day3/aocDay3.c
        Day4/aocDay4.c
        Day4/md5.c
        Day4/md5.h
        Day5/aocDay5.c
        Day6/aocDay6.c)

find_package(Threads REQUIRED)
target_link_libraries(AdventOfCode_2015 Threads::Threads)