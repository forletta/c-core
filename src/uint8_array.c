#include "uint8_array.h"
#include "void_array.h"

uint8_t *Uint8Array_get_ptr(Uint8Array *arr, size_t i) {
    return (uint8_t *)VoidArray_get_ptr((VoidArray *)arr, sizeof(uint8_t), i);
}

uint8_t Uint8Array_get(Uint8Array *arr, size_t i) {
    return *Uint8Array_get_ptr(arr, i);
}
