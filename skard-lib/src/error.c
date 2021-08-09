#include "error.h"

#include <stdio.h>
#include <stdlib.h>


void printError(const char* message)
{
    fprintf(stderr, "ERROR: %s\n", message);
}

void exitError(int code, const char* message)
{
    printError(message);
    exit(code);
}

void exitOutOfMemory()
{
    exitError(CSKARD_EXIT_OUT_OF_MEMORY, "Out of memory.");
}