#include "uint8_array.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    uint8_t items[4] = { 4, 3, 2, 1 };
    Uint8Array arr = {
        .arr = items,
        .len = 4,
    };

    for (size_t i = 0; i < 4; i++) {
        uint8_t n = Uint8Array_get(&arr, i);

        printf("%u", n);
    }

    return 0;
}
