#include "void_array.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>

VoidArray VoidArray_copy(VoidArray *arr, size_t element_size) {
    VoidArray new = {.len = arr->len};

    if ((new.arr = malloc(arr->len * element_size)) == NULL)
        malloc_error();

    memcpy(new.arr, arr->arr, arr->len);

    return new;
}

void *VoidArray_get(VoidArray *arr, size_t element_size, size_t i) {
    if (i < arr->len)
        return arr->arr + i;

    out_of_bounds();
}

void VoidArray_free(VoidArray *arr) {
    free(arr->arr);

    arr->len = 0;
}
