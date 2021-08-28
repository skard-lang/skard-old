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

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
        case OP_RETURN:
            return disassembleSimpleInstruction(chunk, "OP_RETURN", offset);
        case OP_CONSTANT:
            return offset + 1;
        case OP_CONSTANT_LONG:
            return offset + 1;
        default:
            return disassembleUnknownInstruction(instruction, offset);
    }
}

size_t disassembleSimpleInstruction(Chunk *chunk, const char *name, size_t offset)
{
    printLineInfo(chunk, offset);

    printf("%s\n", name);
    return offset + 1;
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
