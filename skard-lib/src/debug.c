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
            return disassembleSimpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            break;
        case OP_CONSTANT_LONG:
            break;
        default:
            return disassembleUnknownInstruction(instruction, offset);
    }
}

size_t disassembleSimpleInstruction(const char *name, size_t offset)
{
    printf("%s\n", name);
    return offset + 1;
}

size_t disassembleUnknownInstruction(uint8_t instruction, size_t offset)
{
    printf("Unknown: %d\n", instruction);
    return offset + 1;
}
