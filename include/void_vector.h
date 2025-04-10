#ifndef VOID_VECTOR_H
#define VOID_VECTOR_H

#include "void_array.h"

typedef struct {
    VoidArray arr;
    size_t cap;
} VoidVector;

size_t VoidVector_reserve(VoidVector *v, size_t element_size, size_t additional);
size_t VoidVector_ensure_capacity(VoidVector *v, size_t element_size, size_t additional);

void *VoidVector_get(VoidVector *v, size_t element_size, size_t i);

#endif // !VOID_VECTOR_H

