/**
 * @file
 */


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

    Value value = {.type = VAL_INT, .as.sk_integer = 204};

    for (int i = 0; i < 100; ++i)
    {
        writeConstant(&c, value, 2);
    }

    Value value2 = {.type = VAL_BOOL, .as.sk_boolean = true};
    writeConstant(&c, value2, 2);

    Value value3 = {.type = VAL_REAL, .as.sk_real = 12.4};
    writeConstant(&c, value3, 3);

    disassembleChunk(&c, "main");

    freeChunk(&c);

    return 0;
}
