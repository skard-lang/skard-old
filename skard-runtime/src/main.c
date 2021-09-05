/**
 * @file
 */


#include "skard.h"
#include <stdio.h>

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
    VM vm;
    initVM(&vm);

    Chunk c;

    initChunk(&c);

    Value value1 = {.type = VAL_INT, .as.sk_int = 1};
    Value value2 = {.type = VAL_INT, .as.sk_int = 3};
    Value value3 = {.type = VAL_INT, .as.sk_int = 0};

    writeConstant(&c, value1, 10);
    writeConstant(&c, value2, 10);
    writeChunk(&c, OP_ADD_INT, 11);
    writeConstant(&c, value3, 11);
    writeChunk(&c, OP_DIVIDE_INT, 11);
    writeChunk(&c, OP_NEGATE_INT, 11);

    writeChunk(&c, OP_RETURN, 12);

    disassembleChunk(&c, "main");

    printf("\n");

    interpret(&vm, &c);

    freeChunk(&c);

    freeVM(&vm);

    return 0;
}
