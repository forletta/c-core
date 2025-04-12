#ifndef VOID_ARRAY_H
#define VOID_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *const ptr;
    const size_t len;
} VoidArray;

VoidArray VoidArray_copy(VoidArray *arr, size_t element_size);
void *const VoidArray_get(VoidArray *arr, size_t element_size, size_t i);

#endif // !VOID_ARRAY_H
