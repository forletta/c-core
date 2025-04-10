#include "uint8_array.h"
#include "void_array.h"

uint8_t *Uint8Array_get(Uint8Array *arr, size_t i) {
    return (uint8_t *)VoidArray_get((VoidArray *)arr, sizeof(uint8_t), i);
}
