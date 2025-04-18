#ifndef ARRAY_H
#define ARRAY_H

#include "test_utils.h"
#include <stddef.h>

typedef struct {
    void *ptr;
    size_t len;
    size_t cap;
} Array;

typedef struct {
    Array *array;
    size_t cursor;
} ArrayIter;

// Array:
// Constructors:

Array Array_take(void *ptr, size_t len);
Array Array_copy(void *ptr, size_t element_size, size_t len);

// Getters:

void *Array_get(Array *array, size_t element_size, size_t i);
Array Array_slice(Array *array, size_t element_size, size_t start, size_t end);
bool Array_is_slice(Array *array);

// Setters:

void Array_reserve(Array *array, size_t element_size, size_t additional);
void Array_ensure_capacity(Array *array, size_t element_size,
                           size_t additional);
void *Array_push(Array *array, size_t element_size);
// void *Array_extend(Array *array, size_t element_size, const Array *src);

// ArrayIter:

ArrayIter ArrayIter_create(Array *array);
void *ArrayIter_peek(ArrayIter *iter, size_t element_size);
void *ArrayIter_next(ArrayIter *iter, size_t element_size);

// Macros:

#define ARRAY(type)                                                            \
    typedef struct {                                                           \
        type *ptr;                                                             \
        size_t len;                                                            \
        size_t cap;                                                            \
    } type##Array;                                                             \
    typedef struct {                                                           \
        type##Array *array;                                                    \
        size_t cursor;                                                         \
    } type##ArrayIter;                                                         \
    type##Array type##Array_take(type *ptr, size_t len);                       \
    type##Array type##Array_copy(type *ptr, size_t len);                       \
    type *type##Array_get(type##Array *array, size_t i);                       \
    type##Array type##Array_slice(type##Array *array, size_t start,            \
                                  size_t end);                                 \
    bool type##Array_is_slice(type##Array *array);                             \
    void type##Array_reserve(type##Array *array, size_t additional);           \
    void type##Array_push(type##Array *array, type element);

#define ARRAY_IMPL(type)                                                       \
    type##Array type##Array_take(type *ptr, size_t len) {                      \
        Array array = Array_take((void *)ptr, len);                            \
        return *(type##Array *)&array;                                         \
    }                                                                          \
    type##Array type##Array_copy(type *ptr, size_t len) {                      \
        Array array = Array_copy((void *)ptr, sizeof(type), len);              \
        return *(type##Array *)&array;                                         \
    }                                                                          \
    type *type##Array_get(type##Array *array, size_t i) {                      \
        return (type *)Array_get((Array *)array, sizeof((array)->ptr[0]), i);  \
    }                                                                          \
    type##Array type##Array_slice(type##Array *array, size_t start,            \
                                  size_t end) {                                \
        Array slice =                                                          \
            Array_slice((Array *)array, sizeof((array)->ptr[0]), start, end);  \
        return *(type##Array *)&slice;                                         \
    }                                                                          \
    bool type##Array_is_slice(type##Array *array) {                            \
        return Array_is_slice((Array *)array);                                 \
    }                                                                          \
    void type##Array_reserve(type##Array *array, size_t additional) {          \
        return Array_reserve((Array *)array, sizeof((array)->ptr[0]),          \
                             additional);                                      \
    }                                                                          \
    void type##Array_push(type##Array *array, type element) {                  \
        *(type *)Array_push((Array *)array, sizeof((array)->ptr[0])) =         \
            element;                                                           \
    }                                                                          \
    type##ArrayIter type##ArrayIter_create(type##Array *array) {               \
        ArrayIter iter = ArrayIter_create((Array *)array);                     \
        return *(type##ArrayIter *)&iter;                                      \
    }                                                                          \
    type *type##ArrayIter_next(type##ArrayIter *iter) {                        \
        return (type *)ArrayIter_next((ArrayIter *)iter,                       \
                                      sizeof((iter)->array->ptr[0]));          \
    }                                                                          \
    type *type##ArrayIter_peek(type##ArrayIter *iter) {                        \
        return (type *)ArrayIter_peek((ArrayIter *)iter,                       \
                                      sizeof((iter)->array->ptr[0]));          \
    }

// Tests:

typedef struct {
    size_t x;
    size_t y;
} ArrayTestType;

ARRAY(ArrayTestType);

bool test_Array_take();
bool test_Array_copy();
bool test_Array_get();
bool test_Array_slice();
bool test_Array_is_slice();
bool test_Array_reserve();
bool test_Array_push();
bool test_ArrayIter_create();
bool test_ArrayIter_peek();
bool test_ArrayIter_next();

static const Test ARRAY_TEST_GROUP[] = {
    TEST(test_Array_take),     TEST(test_Array_copy),
    TEST(test_Array_get),      TEST(test_Array_slice),
    TEST(test_Array_is_slice), TEST(test_Array_reserve),
    TEST(test_Array_push),     TEST(test_ArrayIter_create),
    TEST(test_ArrayIter_peek), TEST(test_ArrayIter_next),
};

#endif // !ARRAY_H
