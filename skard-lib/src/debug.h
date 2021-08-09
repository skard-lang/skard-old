#ifndef CSKARD_DEBUG_H
#define CSKARD_DEBUG_H

#include "chunk.h"

/**
 * @brief
 *
 * @param chunk
 * @param name
 */
void disassembleChunk(Chunk *chunk, const char *name);

/**
 * @brief
 *
 * @param chunk
 * @param offset
 *
 * @return
 */
int disassembleInstruction(Chunk *chunk, int offset);

/**
 * @brief
 *
 * @param name
 * @param offset
 *
 * @return
 */
static int disassembleSimpleInstruction(const char *name, int offset);

/**
 * @brief
 *
 * @param instruction
 * @param offset
 *
 * @return
 */
static int disassembleUnknownInstruction(uint8_t instruction, int offset);

#endif //CSKARD_DEBUG_H
