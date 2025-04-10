#include "ascii_string.h"
#include "void_array.h"
#include "void_vector.h"

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
