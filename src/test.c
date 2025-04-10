// #include "uint8_array.h"
#include "ascii_string.h"
#include "uint8_vector.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    uint8_t items[4] = { 4, 3, 2, 1 };
    Uint8Array arr = {
        .arr = items,
        .len = 4,
    };

    for (size_t i = 0; i < 4; i++) {
        printf("%u", *Uint8Array_get(&arr, i));
    }

    Uint8Vector v = {};

    Uint8Vector_push(&v, 1);
    Uint8Vector_push(&v, 2);
    Uint8Vector_push(&v, 3);

    Uint8Vector_extend_from(&v, &arr);

    AsciiString s = {};

    AsciiString_push(&s, 'h');
    AsciiString_push(&s, 'e');
    AsciiString_push(&s, 'l');
    AsciiString_push(&s, 'l');
    AsciiString_push(&s, 'o');

    printf("%s", s.str.str);

    printf("%c", *AsciiString_get(&s, 1));
    printf("%c", *AsciiString_get(&s, 3));

    for (size_t i = 0; i < v.arr.len; i++) {
        printf("%u", *Uint8Vector_get(&v, i));
    }
    return 0;
}
