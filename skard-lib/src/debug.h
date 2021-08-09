#ifndef CSKARD_DEBUG_H
#define CSKARD_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, int offset);

static int simpleInstruction(const char *name, int offset);
static int unknownInstruction(uint8_t instruction, int offset);

#endif //CSKARD_DEBUG_H
