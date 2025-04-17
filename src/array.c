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

// Tests:

bool test_Array_take() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take(arr, 3);

    ASSERT_EQ(arr, array.ptr);
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
