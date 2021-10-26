#include "chunk.h"

#include "memory.h"


void initChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
}

void writeChunk(Chunk *chunk, uint8_t byte)
{
    if (chunk->capacity < chunk->count + 1)
    {
        size_t oldCapacity = chunk->capacity;
        chunk->capacity = CSKARD_GROW_CAPACITY(oldCapacity);
        chunk->code = CSKARD_GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk *chunk)
{
    CSKARD_FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    initChunk(chunk);
}
