#include "ascii_string.h"
#include "void_array.h"
#include "void_vector.h"
#include <stdlib.h>
#include <string.h>

AsciiStr AsciiStr_copy(const AsciiStr *str) {
    VoidArray void_array = VoidArray_copy((VoidArray *)str, sizeof(char));
    return *(AsciiStr *)&void_array;
}

AsciiStr AsciiStr_copy_from_cstr(const char *cstr) {
    size_t len = strlen(cstr);
    char *ptr = malloc(len);
    memcpy(ptr, cstr, len);

    AsciiStr str = {
        .str = ptr,
        .len = len,
    };

    return str;
}

const char *AsciiStr_get(const AsciiStr *str, size_t i) {
    return (const char *)VoidArray_get((const VoidArray *)str, sizeof(char), i);
}

size_t AsciiString_reserve(AsciiString *str, size_t additional) {
    return VoidVector_reserve((VoidVector *)str, sizeof(char), additional);
}

const char *AsciiString_get(const AsciiString *str, size_t i) {
    return AsciiStr_get(&str->str, i);
}

void AsciiString_push(AsciiString *str, char c) {
    VoidVector_ensure_capacity((VoidVector *)str, sizeof(char), 1);

    str->str.str[str->str.len++] = c;
}

void AsciiString_extend_from(AsciiString *str, const AsciiStr *src) {
    VoidVector_extend_from((VoidVector *)str, sizeof(char), (VoidArray *)src);
}

void AsciiStr_free(AsciiStr *str) { VoidArray_free((VoidArray *)str); }

void AsciiString_free(AsciiString *str) { VoidVector_free((VoidVector *)str); }
