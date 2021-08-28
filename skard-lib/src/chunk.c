#include "chunk.h"

#include "memory.h"

void initLineArray(LineArray *array)
{
    array->capacity = 0;
    array->count = 0;
    array->lines = NULL;
}

void freeLineArray(LineArray *array)
{
    CSKARD_FREE_ARRAY(size_t, array->lines, array->capacity);

    initLineArray(array);
}


void writeNumberLineArray(LineArray *array, size_t number)
{
    if (array->capacity < array->count + 1)
    {
        size_t oldCapacity = array->capacity;
        array->capacity = CSKARD_GROW_CAPACITY(oldCapacity);
        array->lines = CSKARD_GROW_ARRAY(size_t, array->lines, oldCapacity, array->capacity);
    }

    array->lines[array->count] = number;
    array->count++;
}


void addLineArray(LineArray *array, size_t line)
{
    if ((array->count != 0) && (array->lines[array->count - 2] == line))
    {
        array->lines[array->count - 1]++;
        return;
    }

    writeNumberLineArray(array, line);
    writeNumberLineArray(array, 1);
}

size_t getLineLineArray(LineArray *array, size_t offset)
{
    if (array->lines == NULL)
    {
        return 0;
    }

    size_t current = 0;
    while (offset >= array->lines[current + 1])
    {
        offset -= array->lines[current + 1];
        current += 2;
    }

    return array->lines[current];
}


void initChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;

    initLineArray(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk)
{
    CSKARD_FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);

    freeLineArray(&chunk->lines);
    freeValueArray(&chunk->constants);

    initChunk(chunk);
}


size_t getLineChunk(Chunk *chunk, size_t offset)
{
    return getLineLineArray(&chunk->lines, offset);
}


void writeChunk(Chunk *chunk, uint8_t byte, size_t line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        size_t oldCapacity = chunk->capacity;
        chunk->capacity = CSKARD_GROW_CAPACITY(oldCapacity);
        chunk->code = CSKARD_GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    addLineArray(&chunk->lines, line);
}

void writeConstant(Chunk *chunk, Value value, size_t line)
{

}


size_t addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
