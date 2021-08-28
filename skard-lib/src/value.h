#ifndef CSKARD_VALUE_H
#define CSKARD_VALUE_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enum of all possible value types.
 */
typedef enum
{
    VAL_BOOL,
    VAL_REAL,
    VAL_INT
} ValueType;

/**
 * @brief Data structure that holds one value and its type.
 */
typedef struct
{
    ValueType type;
    union
    {
        bool boolean;
        double real;
        int64_t integer;
    } as;
} Value;

typedef struct
{
    int capacity;
    int count;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void writeValueArray(ValueArray *array, Value value);
void freeValueArray(ValueArray *array);

#endif //CSKARD_VALUE_H
