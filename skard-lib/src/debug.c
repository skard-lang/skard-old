#include "debug.h"

#include <stdio.h>

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("=== %s ===\n", name);

    int offset = 0;

    while (offset < chunk->count)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%06d ", offset);

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
        case OP_RETURN:
            return disassembleSimpleInstruction("OP_RETURN", offset);
        default:
            return disassembleUnknownInstruction(instruction, offset);
    }
}

static int simpleInstruction(const char *name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

static int unknownInstruction(uint8_t instruction, int offset)
{
    printf("Unknown: %d\n", instruction);
    return offset + 1;
}
