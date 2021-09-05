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
        bool sk_bool;
        double sk_real;
        int64_t sk_int;
    } as;
} Value;

typedef struct
{
    size_t capacity;
    size_t count;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);
void freeValueArray(ValueArray *array);

void writeValueArray(ValueArray *array, Value value);

#endif //CSKARD_VALUE_H
