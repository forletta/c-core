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

size_t VoidVector_ensure_capacity(VoidVector *v, size_t element_size,
                                  size_t additional) {
    if (v->arr.len < v->cap)
        return 0;

    return VoidVector_reserve(v, element_size, additional);
}

void *VoidVector_get(VoidVector *v, size_t element_size, size_t i) {
    return VoidArray_get(&v->arr, element_size, i);
}

VoidArray VoidVector_extend_from(VoidVector *v, size_t element_size,
                                 VoidArray *src) {
    VoidVector_ensure_capacity(v, element_size, src->len);

    VoidArray slice = {
        .arr = v->arr.arr + v->arr.len,
        .len = src->len,
    };

    memcpy(v->arr.arr + v->arr.len, src->arr, src->len);
    v->arr.len += src->len;

    return slice;
}

void VoidVector_free(VoidVector *v) {
    VoidArray_free(&v->arr);

    v->cap = 0;
}
