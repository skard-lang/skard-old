#ifndef CSKARD_DEBUG_H
#define CSKARD_DEBUG_H

#include "chunk.h"

/**
 * @brief Iterates over chunk and disassembles its instructions.
 *
 * @param chunk pointer to the chunk
 * @param name descriptive name of the chunk (will be displayed in the output)
 */
void disassembleChunk(Chunk *chunk, const char *name);

/**
 * @brief Disassembles one instruction in the chunk printing its name if known.
 *
 * @param chunk pointer to the chunk
 * @param offset offset of the disassembled instruction
 *
 * @return Returns offset of the next instruction depending on the size of the current instruction.
 */
int disassembleInstruction(Chunk *chunk, int offset);

/**
 * @brief Disassembles one simple instruction (with no other associated instructions).
 *
 * @note This function doesn't check if next instruction exists.
 *
 * @param name name of the disassembled instruction (will be displayed in the output)
 * @param offset offset of the disassembled instruction
 *
 * @return Returns possible offset of the next instruction.
 */
static int disassembleSimpleInstruction(const char *name, int offset);

/**
 * @brief Disassembles one unknown instruction (usually wrong byte).
 *
 * @note This function doesn't check if next instruction exists.
 *
 * @param instruction byte value of the instruction
 * @param offset offset of the disassembled instruction
 *
 * @return Returns possible offset of the next instruction.
 */
static int disassembleUnknownInstruction(uint8_t instruction, int offset);

#endif //CSKARD_DEBUG_H
