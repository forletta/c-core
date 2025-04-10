#include "void_vector.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>

size_t VoidVector_reserve(VoidVector *v, size_t element_size,
                          size_t additional) {
    if (additional == 0)
        return v->cap;

    size_t required_capacity = v->cap + additional;
    uint8_t *ptr;

    if ((ptr = malloc(required_capacity * element_size)) == NULL)
        malloc_error();

    memcpy(ptr, v->arr.arr, v->arr.len);
    free(v->arr.arr);
    v->arr.arr = ptr;
    v->cap = required_capacity;

    return v->cap;
}

size_t VoidVector_ensure_capacity(VoidVector *v, size_t element_size, size_t additional) {
    if (v->arr.len < v->cap)
        return 0;

    return VoidVector_reserve(v, element_size, additional);
}

void *VoidVector_get(VoidVector *v, size_t element_size, size_t i) {
    return VoidArray_get(&v->arr, element_size, i);
}
