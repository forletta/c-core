#include "array.h"
#include "c_core_error.h"
#include "test_utils.h"
#include <stdlib.h>
#include <string.h>

ARRAY_IMPL(ArrayTestType);

// Constructors:

Array Array_take(void *ptr, size_t len) {
    return (Array){.ptr = ptr, .len = len, .cap = 0};
}

Array Array_copy(void *ptr, size_t element_size, size_t len) {
    void *new = malloc(len * element_size);
    memcpy(new, ptr, len * element_size);

    return (Array){.ptr = new, .len = len, .cap = len};
}

// Getters:

void *Array_get(Array *array, size_t element_size, size_t i) {
    if (i >= array->len)
        out_of_bounds();

    return array->ptr + (i * element_size);
}

Array Array_slice(Array *array, size_t element_size, size_t start, size_t end) {
    if (start >= array->len || end > array->len)
        out_of_bounds();

    if (start >= end)
        return (Array) {};

    return (Array) {.ptr = Array_get(array, element_size, start), .len = end - start, .cap = 0};
}

// Tests:

bool test_Array_take() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take(arr, 3);

    ASSERT_EQ(array.ptr, arr);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(array.cap, 0);

    return true;
}


bool test_Array_copy() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_copy(arr, 3);

    ASSERT_NE(arr, array.ptr);
    ASSERT_EQ(GET(&array, 0)->x, 1);
    ASSERT_EQ(GET(&array, 1)->x, 3);
    ASSERT_EQ(GET(&array, 2)->x, 5);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(array.cap, 3);

    return true;
}

bool test_Array_get() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };
    ArrayTestTypeArray array = ArrayTestTypeArray_take(arr, 3);

    ASSERT_EQ(GET(&array, 0)->x, 1);
    ASSERT_EQ(GET(&array, 1)->x, 3);
    ASSERT_EQ(GET(&array, 2)->x, 5);

    return true;
}

bool test_Array_slice() {
        ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };
    ArrayTestTypeArray array = ArrayTestTypeArray_take(arr, 3);

    ArrayTestTypeArray slice = ArrayTestTypeArray_slice(&array, 0, 3);
    ASSERT_EQ(slice.len, 3);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(GET(&slice, 0)->x, 1);
    ASSERT_EQ(GET(&slice, 1)->x, 3);
    ASSERT_EQ(GET(&slice, 2)->x, 5);

    slice = ArrayTestTypeArray_slice(&array, 0, 2);
    ASSERT_EQ(slice.len, 2);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(GET(&slice, 0)->x, 1);
    ASSERT_EQ(GET(&slice, 1)->x, 3);

    slice = ArrayTestTypeArray_slice(&array, 1, 3);
    ASSERT_EQ(slice.len, 2);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(GET(&slice, 0)->x, 3);
    ASSERT_EQ(GET(&slice, 1)->x, 5);

    slice = ArrayTestTypeArray_slice(&array, 2, 1);
    ASSERT_EQ(slice.ptr, NULL);
    ASSERT_EQ(slice.len, 0);
    ASSERT_EQ(slice.cap, 0);

    return true;
}

// // Constructors:
//
// void *array_copy(size_t element_size, void *ptr, size_t len) {
//     void *new = array_alloc(element_size, len);
//
//     memcpy(new, ptr, len * element_size);
//
//     return new;
// }
//
// void *array_alloc(size_t element_size, size_t len) {
//     void *ptr;
//
//     if ((ptr = malloc(len * element_size)) == NULL)
//         malloc_error();
//
//     return ptr;
// }
//
// // Getters:
//
// void *array_get(size_t element_size, void *ptr, size_t len, size_t i) {
//     if (i >= len)
//         out_of_bounds();
//
//     return ptr + (i * element_size);
// }
//
// void *array_get_slice(size_t element_size, void *ptr, size_t len, size_t
// start, size_t end) {
//     if (start >= len || end > len)
//         out_of_bounds();
//
//     if (start > end)
//         return NULL;
//
//     return array_get(element_size, ptr, len, start);
// }
