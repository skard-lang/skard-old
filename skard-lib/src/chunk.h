/**
 * @file
 *
 * @brief Chunks of bytecode
 */

#ifndef CSKARD_CHUNK_H
#define CSKARD_CHUNK_H

#include <stdint.h>

#include "value.h"

/**
 * @brief Enum of all available operation codes.
 *
 * @relatedalso Chunk
 */
typedef enum
{
    OP_RETURN,  //!< Return instruction
    OP_CONSTANT,
    OP_CONSTANT_LONG
} OpCode;


/**
 * @brief Data structure that holds one chunk of bytecode.
 *
 */
typedef struct
{
    size_t count;  //!< Number of bytes in chunk
    size_t capacity;  //!< Number of allocated bytes for chunk
    uint8_t *code;  //!< Pointer to the first byte in chunk
    ValueArray constants;
} Chunk;


/**
 * @brief Initializes default values for chunk.
 *
 * @details This must be called before any other function interacts with the chunk.
 *
 * @note The chunk must be uninitialized or freed by freeChunk() before using this function
 *
 * @param chunk pointer to the chunk
 *
 * @relatedalso Chunk
 */
void initChunk(Chunk *chunk);

/**
 * @brief Frees memory allocated for chunk.
 *
 * @details This must be called on every chunk initialized with initChunk() to prevent memory leaks.
 *
 * @param chunk pointer to the chunk
 *
 * @relatedalso Chunk
 */
void freeChunk(Chunk *chunk);


/**
 * @brief Writes one byte of bytecode to the end of the chunk.
 *
 * @note The chunk must be initialized with function initChunk() before using this function for the first time.
 *
 * @param chunk pointer to the chunk
 * @param byte byte to be added to the end of the chunk
 *
 * @relatedalso Chunk
 */
void writeChunk(Chunk *chunk, uint8_t byte);


int add

#endif //CSKARD_CHUNK_H
