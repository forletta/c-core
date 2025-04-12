#include "void_array.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>

VoidArray VoidArray_copy(VoidArray *arr, size_t element_size) {
    void *ptr;

    if ((ptr = malloc(arr->len * element_size)) == NULL)
        malloc_error();

    memcpy(ptr, arr->ptr, arr->len * element_size);

    VoidArray new = {
        .ptr = ptr,
        .len = arr->len,
    };

    return new;
}

void *VoidArray_get(VoidArray *arr, size_t element_size, size_t i) {
    if (i < arr->len)
        return arr->ptr + i;

    out_of_bounds();
}
