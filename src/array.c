#include "array.h"
#include "c_core_error.h"
#include "ext.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void print_free(ArrayTestType *t) {
//     printf("{x = %zu, y = %zu}\n", t->x, t->y);
// }
//
// static const ExtInterface PRINT_EXT = {.free = (FreeFunction)print_free};

ARRAY_IMPL(ArrayTestType, EXT_NULL);

// Constructors:

Array Array_take_ptr(void *ptr, size_t len) {
    return (Array){.ptr = ptr, .len = len, .cap = 0};
}

Array Array_copy_ptr(void *ptr, size_t element_size, size_t len) {
    void *new = malloc(len * element_size);
    memcpy(new, ptr, len * element_size);

    return (Array){.ptr = new, .len = len, .cap = len};
}

Array Array_copy(Array *array, size_t element_size) {
    return Array_copy_ptr(array->ptr, element_size, array->len);
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
        return (Array){};

    return (Array){.ptr = Array_get(array, element_size, start),
                   .len = end - start,
                   .cap = 0};
}

// Setters:

void Array_reserve(Array *array, size_t element_size, size_t additional) {
    if (additional == 0)
        return;

    size_t minimum_capacity =
        (Array_is_slice(array) ? array->len : array->cap) + additional;
    size_t amortized_capacity =
        array->cap * 2 > minimum_capacity ? array->cap * 2 : minimum_capacity;
    size_t required_size = amortized_capacity * element_size;

    void *ptr;

    if ((ptr = malloc(required_size)) == NULL)
        malloc_error();

    memcpy(ptr, array->ptr, array->len * element_size);

    if (!Array_is_slice(array))
        free(array->ptr);

    array->ptr = ptr;
    array->cap = amortized_capacity;
}

bool Array_is_slice(Array *array) { return array->cap == 0; }

void Array_ensure_capacity(Array *array, size_t element_size,
                           size_t additional) {
    if (Array_is_slice(array) || (array->cap - array->len) < additional)
        Array_reserve(array, element_size, additional);
}

void *Array_push(Array *array, size_t element_size) {
    Array_ensure_capacity(array, element_size, 1);

    return array->ptr + (array->len++ * element_size);
}

void Array_free(Array *array, size_t element_size, FreeFunction free_element) {
    if (array->cap != 0) {
        if (free_element != NULL) {
            for (size_t i = 0; i < array->len; i++) {
                free_element(Array_get(array, element_size, i));
            }
        }

        free(array->ptr);
    }

    array->ptr = NULL;
    array->len = 0;
    array->cap = 0;
}

// ArrayIter:

ArrayIter ArrayIter_create(Array *array) {
    return (ArrayIter){.array = array, .cursor = 0};
}

size_t ArrayIter_current_index(ArrayIter *iter) {
    if (iter->cursor == 0)
        out_of_bounds();

    return iter->cursor - 1;
}

void *ArrayIter_current(ArrayIter *iter, size_t element_size) {
    return Array_get(iter->array, element_size, ArrayIter_current_index(iter));
}

void *ArrayIter_peek(ArrayIter *iter, size_t element_size) {
    if (iter->cursor >= iter->array->len)
        return NULL;

    return Array_get(iter->array, element_size, iter->cursor);
}

void *ArrayIter_next(ArrayIter *iter, size_t element_size) {
    if (iter->cursor >= iter->array->len)
        return NULL;

    return Array_get(iter->array, element_size, iter->cursor++);
}

// Tests:

bool test_Array_take_ptr() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ASSERT_EQ(array.ptr, arr);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(array.cap, 0);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_Array_copy_ptr() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_copy_ptr(arr, 3);

    ASSERT_NE(arr, array.ptr);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 2)->x, 5);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(array.cap, 3);

    ArrayTestTypeArray_free(&array);

    return true;
}

bool test_Array_copy() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);
    ArrayTestTypeArray new = ArrayTestTypeArray_copy(&array);

    ASSERT_NE(new.ptr, array.ptr);
    ASSERT_EQ(ArrayTestTypeArray_get(&new, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&new, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&new, 2)->x, 5);
    ASSERT_EQ(new.len, 3);
    ASSERT_EQ(new.cap, 3);

    ArrayTestTypeArray_free(&new);
    ArrayTestTypeArray_free(&array);

    return true;
}

bool test_Array_get() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };
    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 2)->x, 5);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_Array_is_slice() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = {};
    ASSERT_EQ(ArrayTestTypeArray_is_slice(&array), true);
    ArrayTestTypeArray_free(&array); // Not needed

    array = ArrayTestTypeArray_take_ptr(arr, 3);
    ASSERT_EQ(ArrayTestTypeArray_is_slice(&array), true);
    ArrayTestTypeArray_free(&array); // Not needed

    array = ArrayTestTypeArray_copy_ptr(arr, 3);
    ASSERT_EQ(ArrayTestTypeArray_is_slice(&array), false);

    ArrayTestTypeArray_free(&array);

    return true;
}

bool test_Array_slice() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };
    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArray slice = ArrayTestTypeArray_slice(&array, 0, 3);
    ASSERT_EQ(slice.len, 3);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 2)->x, 5);
    ArrayTestTypeArray_free(&slice); // Not needed

    slice = ArrayTestTypeArray_slice(&array, 0, 2);
    ASSERT_EQ(slice.len, 2);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 1)->x, 3);
    ArrayTestTypeArray_free(&slice); // Not needed

    slice = ArrayTestTypeArray_slice(&array, 1, 3);
    ASSERT_EQ(slice.len, 2);
    ASSERT_EQ(slice.cap, 0);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 0)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&slice, 1)->x, 5);
    ArrayTestTypeArray_free(&slice); // Not needed

    slice = ArrayTestTypeArray_slice(&array, 2, 1);
    ASSERT_EQ(slice.ptr, NULL);
    ASSERT_EQ(slice.len, 0);
    ASSERT_EQ(slice.cap, 0);
    ArrayTestTypeArray_free(&slice); // Not needed

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_Array_reserve() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = {};
    ArrayTestTypeArray_reserve(&array, 0);
    ASSERT_EQ(array.ptr, NULL);
    ASSERT_EQ(array.len, 0);
    ASSERT_EQ(array.cap, 0);

    ArrayTestTypeArray_reserve(&array, 4);
    ASSERT_GE(array.cap, 4);
    ArrayTestTypeArray_free(&array);

    array = ArrayTestTypeArray_take_ptr(arr, 3);
    ArrayTestTypeArray_reserve(&array, 4);
    ASSERT_GE(array.cap, 7);
    ASSERT_NE(array.ptr, arr);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 2)->x, 5);
    ArrayTestTypeArray_free(&array); // Not needed

    array = ArrayTestTypeArray_copy_ptr(arr, 3);
    ArrayTestTypeArray_reserve(&array, 4);
    ASSERT_GE(array.cap, 7);
    ASSERT_EQ(array.len, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 1)->x, 3);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 2)->x, 5);
    ArrayTestTypeArray_free(&array);

    return true;
}

bool test_Array_push() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = {};

    ArrayTestTypeArray_push(&array, &(ArrayTestType){.x = 1, .y = 2});
    ASSERT_GE(array.cap, 1);
    ASSERT_EQ(array.len, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ArrayTestTypeArray_free(&array);

    array = (ArrayTestTypeArray){};
    ArrayTestTypeArray_reserve(&array, 4);
    ArrayTestTypeArray_push(&array, &(ArrayTestType){.x = 1, .y = 2});
    ASSERT_GE(array.cap, 4);
    ASSERT_EQ(array.len, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ArrayTestTypeArray_free(&array);

    array = ArrayTestTypeArray_take_ptr(arr, 3);
    ArrayTestTypeArray_push(&array, &(ArrayTestType){.x = 7, .y = 8});
    ASSERT_GE(array.cap, 4);
    ASSERT_EQ(array.len, 4);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 0)->x, 1);
    ASSERT_EQ(ArrayTestTypeArray_get(&array, 3)->x, 7);
    ArrayTestTypeArray_free(&array);

    return true;
}

bool test_ArrayIter_create() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArrayIter iter = ArrayTestTypeArrayIter_create(&array);

    ASSERT_EQ(iter.cursor, 0);
    ASSERT_EQ(iter.array->ptr, array.ptr);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_ArrayIter_current_index() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArrayIter iter = ArrayTestTypeArrayIter_create(&array);

    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current_index(&iter), 0);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current_index(&iter), 1);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current_index(&iter), 2);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_ArrayIter_current() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArrayIter iter = ArrayTestTypeArrayIter_create(&array);

    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current(&iter)->x, 1);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current(&iter)->x, 3);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_current(&iter)->x, 5);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_ArrayIter_peek() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArrayIter iter = ArrayTestTypeArrayIter_create(&array);

    ASSERT_EQ(ArrayTestTypeArrayIter_peek(&iter)->x, 1);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_peek(&iter)->x, 3);
    ArrayTestTypeArrayIter_next(&iter);
    ASSERT_EQ(ArrayTestTypeArrayIter_peek(&iter)->x, 5);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}

bool test_ArrayIter_next() {
    ArrayTestType arr[] = {
        {.x = 1, .y = 2},
        {.x = 3, .y = 4},
        {.x = 5, .y = 6},
    };

    ArrayTestTypeArray array = ArrayTestTypeArray_take_ptr(arr, 3);

    ArrayTestTypeArrayIter iter = ArrayTestTypeArrayIter_create(&array);

    ASSERT_EQ(ArrayTestTypeArrayIter_next(&iter)->x, 1);
    ASSERT_EQ(ArrayTestTypeArrayIter_next(&iter)->x, 3);
    ASSERT_EQ(ArrayTestTypeArrayIter_next(&iter)->x, 5);

    ArrayTestTypeArray_free(&array); // Not needed

    return true;
}
