#include "uint8_array.h"
#include "c_core_error.h"

uint8_t *Uint8Array_get_ptr(Uint8Array *arr, size_t i) {
    if (i < arr->len)
        return arr->arr + i;

    out_of_bounds();
}

uint8_t Uint8Array_get(Uint8Array *arr, size_t i) {
    return *Uint8Array_get_ptr(arr, i);
}
