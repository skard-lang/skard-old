#include "debug.h"

#include <stdio.h>

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("=== %s ===\n", name);

    size_t offset = 0;

    while (offset < chunk->count)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

size_t disassembleInstruction(Chunk *chunk, size_t offset)
{
    printf("%06zu ", offset);

    printLineInfo(chunk, offset);

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
        case OP_RETURN:
            return disassembleSimpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return disassembleConstantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return offset + 1;
        default:
            return disassembleUnknownInstruction(instruction, offset);
    }
}

size_t disassembleSimpleInstruction(const char *name, size_t offset)
{
    printf("%s\n", name);
    return offset + 1;
}

size_t disassembleConstantInstruction(const char *name, Chunk *chunk, size_t offset)
{
    printf("%-24s ", name);

    size_t index = chunk->code[offset + 1];
    printf("%8zu ", index);
    printValue(chunk->constants.values[index]);

    printf("\n");

    return offset +2;
}

size_t disassembleUnknownInstruction(uint8_t instruction, size_t offset)
{
    printf("Unknown: %d\n", instruction);
    return offset + 1;
}

void printLineInfo(Chunk *chunk, size_t offset)
{
    size_t line = getLineChunk(chunk, offset);
    if ((offset != 0) && (line == getLineChunk(chunk, offset - 1)))
    {
        for (int i = 0; i < 7; i++)
        {
            printf(" ");
        }
        printf("| ");
    }
    else
    {
        printf("%8zu ", line);
    }
}

void printValue(Value value)
{
    printf("{ ");

    switch (value.type)
    {
        case VAL_BOOL:
            break;
        case VAL_REAL:
            break;
        case VAL_INT:
            printf("%lli", value.as.sk_integer);
            break;
        default:
            break;
    }

    printf(" }");
}
