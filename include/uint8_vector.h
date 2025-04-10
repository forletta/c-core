#ifndef UINT8_VECTOR_H
#define UINT8_VECTOR_H

#include "uint8_array.h"

typedef struct {
    Uint8Array arr;
    size_t cap;
} Uint8Vector;

size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional);

uint8_t Uint8Vector_get(Uint8Vector *v, size_t i);
void Uint8Vector_push(Uint8Vector *v, uint8_t value);

#endif // !UINT8_VECTOR_H
