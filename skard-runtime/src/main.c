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
    VM vm;
    initVM(&vm);

    Chunk c;

    initChunk(&c);

    Value value = {.type = VAL_INT, .as.sk_integer = 204};

    for (int i = 0; i < 300; ++i)
    {
        writeConstant(&c, value, 2);
    }

    Value value2 = {.type = VAL_BOOL, .as.sk_boolean = true};
    writeConstant(&c, value2, 2);

    Value value3 = {.type = VAL_REAL, .as.sk_real = 12.4};
    writeConstant(&c, value3, 3);

    writeChunk(&c, OP_RETURN, 1);

    disassembleChunk(&c, "main");

    interpret(&vm, &c);

    freeChunk(&c);

    freeVM(&vm);

    return 0;
}
