// #include "uint8_array.h"
#include "uint8_vector.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // uint8_t items[4] = { 4, 3, 2, 1 };
    // Uint8Array arr = {
    //     .arr = items,
    //     .len = 4,
    // };
    //
    // for (size_t i = 0; i < 4; i++) {
    //     uint8_t n = Uint8Array_get(&arr, i);
    //
    //     printf("%u", n);
    // }

    Uint8Vector v = {};

    Uint8Vector_push(&v, 1);
    Uint8Vector_push(&v, 2);
    Uint8Vector_push(&v, 3);

    for (size_t i = 0; i < v.arr.len; i++) {
        printf("%u", Uint8Vector_get(&v, i));
    }
    return 0;
}
