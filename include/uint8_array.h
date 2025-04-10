#ifndef UINT8_ARRAY_H_
#define UINT8_ARRAY_H_

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *arr;
    size_t len;
} Uint8Array;

uint8_t *Uint8Array_get(Uint8Array *arr, size_t i);
void Uint8Array_free(Uint8Array *arr);

#endif // !UINT8_ARRAY_H_
