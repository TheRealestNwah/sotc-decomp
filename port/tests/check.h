/* A minimal test harness: CHECK records a failure and carries on. */
#ifndef SOTC_PORT_TESTS_CHECK_H
#define SOTC_PORT_TESTS_CHECK_H

#include <stdio.h>

static int check_failures;

#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #cond); \
            check_failures++;                                                    \
        }                                                                        \
    } while (0)

#define CHECK_EQ(a, b) CHECK((a) == (b))

static int check_finish(const char *name)
{
    if (check_failures) {
        fprintf(stderr, "%s: %d check(s) failed\n", name, check_failures);
        return 1;
    }
    printf("%s: all checks passed\n", name);
    return 0;
}

#endif
