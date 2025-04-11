#include "uint8_array.h"
#include "void_array.h"

const uint8_t *Uint8Array_get(const Uint8Array *arr, size_t i) {
    return (const uint8_t *)VoidArray_get((const VoidArray *)arr,
                                          sizeof(uint8_t), i);
}

void Uint8Array_free(Uint8Array *arr) { VoidArray_free((VoidArray *)arr); }
