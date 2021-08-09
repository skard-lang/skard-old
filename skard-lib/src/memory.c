#include "memory.h"

#include <stdlib.h>

#include "error.h"


void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    void *new = realloc(pointer, newSize);

    if (new == NULL)
    {
        exitOutOfMemory();
    }

    return new;
}
