#ifndef ARRAY_H
#define ARRAY_H

#include "test_utils.h"
#include <stddef.h>

typedef struct {
    void *ptr;
    size_t len;
    size_t cap;
} Array;

// Constructors:

Array Array_take(void *ptr, size_t len);
Array Array_copy(void *ptr, size_t element_size, size_t len);

// Getters:

void *Array_get(Array *array, size_t element_size, size_t i);
// void *Array_slice(Array *array, size_t element_size, size_t start, size_t end);

// Macros:

#define ARRAY(type)                                                            \
    typedef struct {                                                           \
        type *ptr;                                                             \
        size_t len;                                                            \
        size_t cap;                                                            \
    } type##Array;                                                             \
    type##Array type##Array_take(type *ptr, size_t len);                       \
    type##Array type##Array_copy(type *ptr, size_t len);

#define ARRAY_IMPL(type)                                                       \
    type##Array type##Array_take(type *ptr, size_t len) {                      \
        Array array = Array_take((void *)ptr, len);                            \
        return *(type##Array *)&array;                                         \
    }                                                                          \
    type##Array type##Array_copy(type *ptr, size_t len) {                      \
        Array array = Array_copy((void *)ptr, sizeof(type), len);              \
        return *(type##Array *)&array;                                         \
    }

#define GET(array, i)                                                          \
    ((typeof((array)->ptr[0]) *)Array_get((Array *)array,                      \
                                          sizeof((array)->ptr[0]), i))

// Tests:

typedef struct {
    size_t x;
    size_t y;
} ArrayTestType;

ARRAY(ArrayTestType);

bool test_Array_take();
bool test_Array_copy();
bool test_Array_get();

static const Test ARRAY_TEST_GROUP[] = {
    TEST(test_Array_take),
    TEST(test_Array_copy),
    TEST(test_Array_get),
};

#endif // !ARRAY_H
