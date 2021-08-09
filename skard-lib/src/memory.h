/**
 * @file
 *
 * @brief Functions and macros for memory management
 */

#ifndef CSKARD_MEMORY_H
#define CSKARD_MEMORY_H

#include <stdint.h>

/**
 * @brief Increases a capacity value which is used for dynamic arrays.
 *
 * @details If the value is less than 8, it returns 0. If the value is at least 8, it returns double of the previous
 * value.
 *
 * @see CSKARD_GROW_ARRAY()
 *
 * @param capacity current capacity value (can be 0)
 */
#define CSKARD_GROW_CAPACITY(capacity) \
((capacity) < 8 ? 8 : (capacity) * 2)

/**
 * @brief Reallocates array to increase its capacity or to initialize it.
 *
 * @see CSKARD_GROW_CAPACITY().
 *
 * @param type type of values located in the array
 * @param pointer pointer to the array which will be grown (can be NULL)
 * @param oldCapacity current capacity of the array (can be 0)
 * @param newCapacity new capacity of the array
 */
#define CSKARD_GROW_ARRAY(type, pointer, oldCapacity, newCapacity) \
(type *) reallocate(pointer, sizeof(type) * (oldCapacity), sizeof(type) * (newCapacity))

/**
 * @brief Frees array.
 *
 * @see CSKARD_GROW_ARRAY().
 *
 * @param type type of values located in the array
 * @param pointer pointer to the array which will be freed
 * @param capacity current capacity of the array
 */
#define CSKARD_FREE_ARRAY(type, pointer, capacity) \
reallocate(pointer, sizeof(type) * (capacity), 0)

/**
 * @brief Reallocates memory
 *
 * @details This is a wrapper around realloc and free. It contains basic error handling.
 *
 * @param pointer pointer to the memory area to be changed (can be NULL)
 * @param oldSize old size of memory area in bytes (can be 0)
 * @param newSize new size of memory area in bytes (can be 0)
 *
 * @return On success, returns the pointer to the beginning of newly allocated memory or NULL if newSize is 0.
 * Freeing is left for the caller. On failure, exits the program with an appropriate exit code and error message.
 *
 * @todo Handle failure better
 */
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif //CSKARD_MEMORY_H
