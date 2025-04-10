#include "ascii_string.h"
#include "void_array.h"
#include "void_vector.h"
#include <string.h>

AsciiStr AsciiStr_copy(AsciiStr *str) {
    VoidArray void_array = VoidArray_copy((VoidArray *)str, sizeof(char));
    return *(AsciiStr *)&void_array;
}

AsciiStr AsciiStr_copy_from_cstr(char *cstr) {
    AsciiStr str = {
        .str = cstr,
        .len = strlen(cstr),
    };

    return AsciiStr_copy(&str);
}

char *AsciiStr_get(AsciiStr *str, size_t i) {
    return (char *)VoidArray_get((VoidArray *)str, sizeof(char), i);
}

size_t AsciiString_reserve(AsciiString *str, size_t additional) {
    return VoidVector_reserve((VoidVector *)str, sizeof(char), additional);
}

char *AsciiString_get(AsciiString *str, size_t i) {
    return AsciiStr_get(&str->str, i);
}

void AsciiString_push(AsciiString *str, char c) {
    VoidVector_ensure_capacity((VoidVector *)str, sizeof(char), 1);

    str->str.str[str->str.len++] = c;
}

AsciiStr AsciiString_extend_from(AsciiString *str, AsciiStr *src) {
    VoidArray void_slice = VoidVector_extend_from((VoidVector *)str, sizeof(char), (VoidArray *)src);

    AsciiStr slice = {
        .str = void_slice.arr,
        .len = void_slice.len,
    };

    return slice;
}
