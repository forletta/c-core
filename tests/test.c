// #include "uint8_array.h"
#include "ascii_string.h"
#include "io.h"
#include "uint8_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    uint8_t items[4] = { 4, 3, 2, 1 };
    Uint8Array arr = {
        .arr = items,
        .len = 4,
    };

    for (size_t i = 0; i < 4; i++) {
        printf("%u\n", *Uint8Array_get(&arr, i));
    }

    Uint8Vector v = {};

    Uint8Vector_push(&v, 1);
    Uint8Vector_push(&v, 2);
    Uint8Vector_push(&v, 3);

    Uint8Vector_extend_from(&v, &arr);

    AsciiString string = {};

    AsciiString_push(&string, 'h');
    AsciiString_push(&string, 'e');
    AsciiString_push(&string, 'l');
    AsciiString_push(&string, 'l');
    AsciiString_push(&string, 'o');

    AsciiStr str = AsciiStr_copy_from_cstr(" there");

    AsciiString_extend_from(&string, &str);

    printf("%s\n", string.str.str);

    printf("%c\n", *AsciiString_get(&string, 1));
    printf("%c\n", *AsciiString_get(&string, 3));

    for (size_t i = 0; i < v.arr.len; i++) {
        printf("%u\n", *Uint8Vector_get(&v, i));
    }

    io_getline(&string, stdin);
    printf("%.*s", (int)string.str.len, string.str.str);

    AsciiString_free(&string);
    AsciiStr_free(&str);
    Uint8Vector_free(&v);

    return 0;
}
