#include "uint8_array.h"
#include "void_array.h"

uint8_t *const Uint8Array_get(const Uint8Array *arr, size_t i) {
    return (uint8_t *const)VoidArray_get((const VoidArray *)arr,
                                          sizeof(uint8_t), i);
}

void Uint8Array_free(Uint8Array *arr) { VoidArray_free((VoidArray *)arr); }
