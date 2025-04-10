#include "uint8_vector.h"
#include "c_core_error.h"
#include "uint8_array.h"
#include <stdlib.h>
#include <string.h>

size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional) {
    if (additional == 0)
        return v->cap;

    size_t required_capacity = v->cap + additional;
    uint8_t *ptr;

    if ((ptr = malloc(required_capacity * sizeof(uint8_t))) == NULL)
        malloc_error();

    memcpy(ptr, v->arr.arr, v->arr.len);
    free(v->arr.arr);
    v->arr.arr = ptr;
    v->cap = required_capacity;

    return v->cap;
}

uint8_t Uint8Vector_get(Uint8Vector *v, size_t i) {
    return Uint8Array_get(&v->arr, i);
}

void Uint8Vector_push(Uint8Vector *v, uint8_t value) {
    if (v->arr.len == v->cap)
        Uint8Vector_reserve(v, v->cap < 8 ? 8 : v->cap);

    v->arr.arr[v->arr.len] = value;
    v->arr.len += 1;
}
