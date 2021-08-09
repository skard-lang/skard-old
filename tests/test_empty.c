#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include "unit_common.h"

#include <cmocka.h>

#include "skard.h"

static void null_test_success(void **state)
{
    (void) state;
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}