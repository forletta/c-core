#ifndef VOID_ARRAY_H
#define VOID_ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *arr;
    size_t len;
} VoidArray;

void *VoidArray_get_ptr(VoidArray *arr, size_t element_size, size_t i);

#endif // !VOID_ARRAY_H
