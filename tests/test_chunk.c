#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdlib.h>

#include "unit_common.h"

#include <cmocka.h>

#include "skard.h"


static int setup_chunk(void **state)
{
    Chunk *c = malloc(sizeof(Chunk));
    if (c == NULL)
    {
        return -1;
    }

    initChunk(c);

    *state = c;

    return 0;
}

static int teardown_chunk(void **state)
{
    free(*state);

    return 0;
}

static void initChunk_uninitialized_countIsZero(void **state)
{
    Chunk *c = *state;

    assert_int_equal(c->count, 0);
}

static void initChunk_uninitialized_capacityIsZero(void **state)
{
    Chunk *c = *state;

    assert_int_equal(c->capacity, 0);
}

static void initChunk_uninitialized_codeIsNull(void **state)
{
    Chunk *c = *state;

    assert_null(c->code);
}

static void writeChunk_initialized_getsChunkToCorrectState(void **state)
{
    Chunk *c = *state;

    writeChunk(c, 0);

    assert_int_not_equal(c->capacity, 0);
    assert_int_equal(c->count, 1);
    assert_non_null(c->code);
}

static void writeChunk_initialized_writesCorrectByteToTheChunk(void **state)
{
    Chunk *c = *state;

    writeChunk(c, 0);
    writeChunk(c, 2);
    writeChunk(c, 42);
    writeChunk(c, 255);

    assert_int_equal(c->code[0], 0);
    assert_int_equal(c->code[1], 2);
    assert_int_equal(c->code[2], 42);
    assert_int_equal(c->code[3], 255);
}

static void writeChunk_eightElements_increasesCapacity(void **state)
{
    Chunk *c = *state;

    writeChunk(c, 0);

    int oldCapacity = c->capacity;

    for (int i = 0; i < 8; i++)
    {
        writeChunk(c, 0);
    }

    assert_true(c->capacity > oldCapacity);
}

static void writeChunk_eightElements_codeIsNotNull(void **state)
{
    Chunk *c = *state;

    writeChunk(c, 0);

    int oldCapacity = c->capacity;

    for (int i = 0; i < 8; i++)
    {
        writeChunk(c, 0);
    }

    assert_non_null(c->code);
}

static void writeChunk_eightElements_writesCorrectByteToTheChunk(void **state)
{
    Chunk *c = *state;

    writeChunk(c, 0);

    int oldCapacity = c->capacity;

    for (int i = 0; i < 8; i++)
    {
        writeChunk(c, 0);
    }

    writeChunk(c, 42);
    writeChunk(c, 128);
    writeChunk(c, 255);


    assert_int_equal(c->code[8], 0);
    assert_int_equal(c->code[9], 42);
    assert_int_equal(c->code[10], 128);
    assert_int_equal(c->code[11], 255);
}

static void freeChunk_initialized_countIsZero(void **state)
{
    Chunk *c = *state;

    freeChunk(c);

    assert_int_equal(c->count, 0);
}

static void freeChunk_initialized_capacityIsZero(void **state)
{
    Chunk *c = *state;

    freeChunk(c);

    assert_int_equal(c->capacity, 0);
}

static void freeChunk_initialized_codeIsNull(void **state)
{
    Chunk *c = *state;

    freeChunk(c);

    assert_null(c->code);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(initChunk_uninitialized_countIsZero, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(initChunk_uninitialized_capacityIsZero, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(initChunk_uninitialized_codeIsNull, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(writeChunk_initialized_getsChunkToCorrectState, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(writeChunk_initialized_writesCorrectByteToTheChunk, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(writeChunk_eightElements_increasesCapacity, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(writeChunk_eightElements_codeIsNotNull, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(writeChunk_eightElements_writesCorrectByteToTheChunk, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(freeChunk_initialized_countIsZero, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(freeChunk_initialized_capacityIsZero, setup_chunk, teardown_chunk),
            cmocka_unit_test_setup_teardown(freeChunk_initialized_codeIsNull, setup_chunk, teardown_chunk),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}