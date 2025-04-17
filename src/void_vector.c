#include "void_vector.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>

// VoidVector VoidVector_copy(VoidVector *v) {
//     VoidArray arr = {.ptr = v->ptr, .len = *v->len};
//     VoidArray new_arr = VoidArray_copy(&arr, v->element_size);
//
//     VoidVector new = {
//         .ptr = new_arr.ptr, .len = new_arr.len, .cap = new_arr.len};
//
//     return new;
// }

size_t VoidVector_reserve(VoidVector *v, size_t additional) {
    if (additional == 0)
        return *v->cap;

    size_t required_capacity = *v->cap + additional;
    uint8_t *ptr;

    if ((ptr = malloc(required_capacity * v->element_size)) == NULL)
        malloc_error();

    memcpy(ptr, *v->ptr, *v->len * v->element_size);
    free(*v->ptr);
    *v->ptr = ptr;
    *v->cap = required_capacity;

    return *v->cap;
}

size_t VoidVector_ensure_capacity(VoidVector *v, size_t additional) {
    if (*v->len < *v->cap)
        return 0;

    return VoidVector_reserve(v, additional);
}

void *VoidVector_get(VoidVector *v, size_t i) {
    if (i < *v->len)
        return *v->ptr + i;

    out_of_bounds();
}

void *VoidVector_push(VoidVector *v) {
    VoidVector_ensure_capacity(v, 1);

    return *v->ptr + ((*v->len)++ * v->element_size);
}

void VoidVector_extend_from(VoidVector *v, VoidArray *src) {
    VoidVector_ensure_capacity(v, src->len);

    memcpy(*v->ptr + *v->len, src->ptr, src->len);
    v->len += src->len;
}

void VoidVector_free(VoidVector *v) {
    free(*v->ptr);

    v->ptr = NULL;
    v->len = 0;
    v->cap = 0;
}
