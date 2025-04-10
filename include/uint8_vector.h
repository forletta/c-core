#ifndef UINT8_VECTOR_H
#define UINT8_VECTOR_H

#include "uint8_array.h"

typedef struct {
    Uint8Array arr;
    size_t cap;
} Uint8Vector;

size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional);

uint8_t *Uint8Vector_get(Uint8Vector *v, size_t i);
void Uint8Vector_push(Uint8Vector *v, uint8_t value);
Uint8Array Uint8Vector_extend_from(Uint8Vector *v, Uint8Array *src);

void Uint8Vector_free(Uint8Vector *arr);

#endif // !UINT8_VECTOR_H
