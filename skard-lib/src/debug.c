#include "debug.h"

#include <stdio.h>

#define CSKARD_DEBUG_STRINGIFY2(x) #x
#define CSKARD_DEBUG_STRINGIFY(x) CSKARD_DEBUG_STRINGIFY2(x)

#define CSKARD_DEBUG_INSTRUCTION_NUMBER_MAX_LENGTH 6
#define CSKARD_DEBUG_LINE_NUMBER_MAX_LENGTH 8
#define CSKARD_DEBUG_INSTRUCTION_NAME_MAX_LENGTH 24
#define CSKARD_DEBUG_CONSTANT_ADDRESS_MAX_LENGTH 8
#define CSKARD_DEBUG_VALUE_MAX_LENGTH 24

int getTableHeaderTotalLength()
{
    int totalLength = 0;
    totalLength += CSKARD_DEBUG_INSTRUCTION_NUMBER_MAX_LENGTH + 1;
    totalLength += CSKARD_DEBUG_LINE_NUMBER_MAX_LENGTH + 1;
    totalLength += CSKARD_DEBUG_INSTRUCTION_NAME_MAX_LENGTH + 1;
    totalLength += CSKARD_DEBUG_CONSTANT_ADDRESS_MAX_LENGTH + 1;
    totalLength += CSKARD_DEBUG_VALUE_MAX_LENGTH + 1;
    totalLength -= 1;

    return totalLength;
}

void printTableHeader(const char *name)
{
    printf("=== CHUNK: %s ===\n", name);

    printf(""
           "%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_INSTRUCTION_NUMBER_MAX_LENGTH) "s|"
           "%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_LINE_NUMBER_MAX_LENGTH) "s|"
           "%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_INSTRUCTION_NAME_MAX_LENGTH) "s|"
           "%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_CONSTANT_ADDRESS_MAX_LENGTH) "s|"
           "%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_VALUE_MAX_LENGTH) "s"
           "\n",
           "NUMBER",
           "LINE",
           "INSTRUCTION NAME",
           "ADDRESS",
           "VALUE"
    );

    int totalLength = getTableHeaderTotalLength();

    for (int i = 0; i < totalLength; i++)
    {
        printf("_");
    }

    printf("\n");
}

void disassembleChunk(Chunk *chunk, const char *name)
{
    printTableHeader(name);

    size_t offset = 0;

    while (offset < chunk->count)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

size_t disassembleInstruction(Chunk *chunk, size_t offset)
{
    printf("%0" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_INSTRUCTION_NUMBER_MAX_LENGTH) "zu ", offset);

    printLineInfo(chunk, offset);

    uint8_t instruction = chunk->code[offset];

    switch (instruction)
    {
        case OP_RETURN:
            return disassembleSimpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return disassembleConstantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return disassembleLongConstantInstruction("OP_LONG_CONSTANT", chunk, offset);
        default:
            return disassembleUnknownInstruction(instruction, offset);
    }
}

size_t disassembleSimpleInstruction(const char *name, size_t offset)
{
    printName(name);
    printf("\n");
    return offset + 1;
}

size_t disassembleConstantInstruction(const char *name, Chunk *chunk, size_t offset)
{
    printName(name);

    size_t index = chunk->code[offset + 1];
    printf("%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_CONSTANT_ADDRESS_MAX_LENGTH) "zu ", index);
    printValue(chunk->constants.values[index]);

    printf("\n");

    return offset + 2;
}

size_t disassembleLongConstantInstruction(const char *name, Chunk *chunk, size_t offset)
{
    printName(name);

    size_t index = chunk->code[offset + 1] | (chunk->code[offset + 2] << 8) | (chunk->code[offset + 3] << 16);
    printf("%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_CONSTANT_ADDRESS_MAX_LENGTH) "zu ", index);
    printValue(chunk->constants.values[index]);

    printf("\n");

    return offset + 4;
}

size_t disassembleUnknownInstruction(uint8_t instruction, size_t offset)
{
    printf("Unknown: %d\n", instruction);
    return offset + 1;
}

void printName(const char *name)
{
    printf("%-" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_INSTRUCTION_NAME_MAX_LENGTH) "s ", name);
}

void printLineInfo(Chunk *chunk, size_t offset)
{
    size_t line = getLineChunk(chunk, offset);
    if ((offset != 0) && (line == getLineChunk(chunk, offset - 1)))
    {
        for (int i = 0; i < (CSKARD_DEBUG_LINE_NUMBER_MAX_LENGTH - 1); i++)
        {
            printf(" ");
        }
        printf("| ");
    }
    else
    {
        printf("%" CSKARD_DEBUG_STRINGIFY(CSKARD_DEBUG_LINE_NUMBER_MAX_LENGTH) "zu ", line);
    }
}

void printValue(Value value)
{
    printf("{ ");

    switch (value.type)
    {
        case VAL_BOOL:
            printf(value.as.sk_boolean ? "true" : "false");
            break;
        case VAL_REAL:
            printf("%g", value.as.sk_real);
            break;
        case VAL_INT:
            printf("%lli", value.as.sk_integer);
            break;
        default:
            break;
    }

    printf(" }");
}
