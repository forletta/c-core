#include "void_array.h"
#include "c_core_error.h"

void *VoidArray_get(VoidArray *arr, size_t element_size, size_t i) {
    if (i < arr->len)
        return arr->arr + i;

    out_of_bounds();
}
