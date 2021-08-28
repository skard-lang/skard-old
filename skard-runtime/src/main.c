/**
 * @file
 */


#include <stdio.h>

#include "skard.h"

/**
 * @brief Skard Runtime entry point
 *
 * @param argc number of input arguments
 * @param argv array of input arguments
 *
 * @return exit code
 */
int main(int argc, const char *argv[])
{
    Chunk c;

    initChunk(&c);
    writeChunk(&c, OP_RETURN, 1);
    writeChunk(&c, OP_RETURN, 1);
    writeChunk(&c, OP_RETURN, 1);

    writeChunk(&c, OP_RETURN, 2);
    writeChunk(&c, OP_RETURN, 2);
    writeChunk(&c, OP_RETURN, 2);
    writeChunk(&c, OP_RETURN, 2);

    writeChunk(&c, OP_RETURN, 3);

    writeChunk(&c, OP_RETURN, 4);

    writeChunk(&c, OP_RETURN, 5);
    writeChunk(&c, OP_RETURN, 5);

    writeChunk(&c, OP_RETURN, 1246165);

    disassembleChunk(&c, "main");

    freeChunk(&c);

    return 0;
}
