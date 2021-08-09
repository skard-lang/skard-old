#ifndef CSKARD_VALUE_H
#define CSKARD_VALUE_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief
 */
typedef enum
{
    VAL_BOOL,
    VAL_REAL,
    VAL_INT
} ValueType;

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

#endif //CSKARD_VALUE_H
