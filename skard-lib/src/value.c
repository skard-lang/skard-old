#include "value.h"

#include "memory.h"

void initValueArray(ValueArray *array)
{
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void writeValueArray(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = CSKARD_GROW_CAPACITY(oldCapacity);
        array->values = CSKARD_GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray *array)
{
    CSKARD_FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}
