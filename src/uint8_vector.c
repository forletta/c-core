#include "uint8_vector.h"
#include "uint8_array.h"
#include "void_vector.h"
#include <stdlib.h>
#include <string.h>

size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional) {
    return VoidVector_reserve((VoidVector *)v, sizeof(uint8_t), additional);
}

uint8_t Uint8Vector_get(Uint8Vector *v, size_t i) {
    return Uint8Array_get(&v->arr, i);
}

void Uint8Vector_push(Uint8Vector *v, uint8_t value) {
    VoidVector_ensure_capacity((VoidVector *)v, sizeof(uint8_t), 1);

    v->arr.arr[v->arr.len] = value;
    v->arr.len += 1;
}
