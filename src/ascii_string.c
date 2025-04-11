#include "ascii_string.h"
#include "c_core_error.h"
#include "void_array.h"
#include "void_vector.h"
#include <stdlib.h>
#include <string.h>

// AsciiStr constructors:

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

// AsciiStr getters:

char *const AsciiStr_get(const AsciiStr *str, size_t i) {
    return (char *const)VoidArray_get((const VoidArray *)str, sizeof(char), i);
}

const AsciiStr AsciiStr_substr(const AsciiStr *str, size_t start, size_t end) {
    AsciiStr substr = {};

    if (start >= str->len || end > str->len)
        out_of_bounds();

    if (start >= end)
        return substr;

    substr.str = AsciiStr_get(str, start);
    substr.len = end - start;

    return substr;
}

// AsciiString getters:

char *const AsciiString_get(const AsciiString *str, size_t i) {
    return AsciiStr_get(&str->str, i);
}

const AsciiStr AsciiString_substr(const AsciiString *str, size_t start, size_t end) {
    AsciiStr substr = {};

    if (start >= str->str.len || end > str->str.len)
        out_of_bounds();

    if (start >= end)
        return substr;

    substr.str = AsciiString_get(str, start);
    substr.len = end - start;

    return substr;
}

// AsciiString setters:

void AsciiString_push(AsciiString *str, char c) {
    VoidVector_ensure_capacity((VoidVector *)str, sizeof(char), 1);

    str->str.str[str->str.len++] = c;
}

void AsciiString_extend_from(AsciiString *str, const AsciiStr *src) {
    VoidVector_extend_from((VoidVector *)str, sizeof(char), (VoidArray *)src);
}

size_t AsciiString_reserve(AsciiString *str, size_t additional) {
    return VoidVector_reserve((VoidVector *)str, sizeof(char), additional);
}

// Destructors:

void AsciiStr_free(AsciiStr *str) { VoidArray_free((VoidArray *)str); }

void AsciiString_free(AsciiString *str) { VoidVector_free((VoidVector *)str); }
