#ifndef VOID_ARRAY_H
#define VOID_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *arr;
    size_t len;
} VoidArray;

VoidArray VoidArray_copy(const VoidArray *arr, size_t element_size);
void *const VoidArray_get(const VoidArray *arr, size_t element_size, size_t i);

void VoidArray_free(VoidArray *arr);

#endif // !VOID_ARRAY_H
