#ifndef UINT8_VECTOR_H
#define UINT8_VECTOR_H

#include "uint8_array.h"

typedef struct {
    Uint8Array arr;
    size_t cap;
} Uint8Vector;

size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional);

const uint8_t *Uint8Vector_get(const Uint8Vector *v, size_t i);
void Uint8Vector_push(Uint8Vector *v, uint8_t value);
void Uint8Vector_extend_from(Uint8Vector *v, const Uint8Array *src);

void Uint8Vector_free(Uint8Vector *arr);

#endif // !UINT8_VECTOR_H
