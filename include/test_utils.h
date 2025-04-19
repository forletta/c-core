#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdbool.h>
#include <stddef.h>

#define TEST(test_) {.name = #test_, .test = test_}
#define TEST_GROUP(tests)                                                      \
    {.ptr = tests, .len = (sizeof(tests) / sizeof(tests[0]))}
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define ASSERT_EQ(rhs, lhs)                                                    \
    if (rhs != lhs)                                                            \
        return false;
#define ASSERT_NE(rhs, lhs)                                                    \
    if (rhs == lhs)                                                            \
        return false;
#define ASSERT_LT(rhs, lhs)                                                    \
    if (rhs >= lhs)                                                            \
        return false;
#define ASSERT_GT(rhs, lhs)                                                    \
    if (rhs <= lhs)                                                            \
        return false;
#define ASSERT_LE(rhs, lhs)                                                    \
    if (rhs > lhs)                                                             \
        return false;
#define ASSERT_GE(rhs, lhs)                                                    \
    if (rhs < lhs)                                                             \
        return false;

typedef struct {
    const char *name;
    bool (*test)(void);
} Test;

typedef struct {
    const Test *ptr;
    size_t len;
} TestGroup;

#endif // !TEST_UTILS_H
