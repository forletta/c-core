#include "ascii_string.h"
#include "c_core_error.h"
#include "void_array.h"
#include "void_vector.h"
#include <stdlib.h>
#include <string.h>

// AsciiStr constructors:

AsciiStr AsciiStr_copy(AsciiStr *str) {
    VoidArray void_array = VoidArray_copy((VoidArray *)str, sizeof(char));
    return *(AsciiStr *)&void_array;
}

AsciiStr AsciiStr_copy_from_cstr(char *cstr) {
    size_t len = strlen(cstr);
    char *ptr = malloc(len);
    memcpy(ptr, cstr, len);

    AsciiStr str = {
        .ptr = ptr,
        .len = len,
    };

    return str;
}

// AsciiStr getters:

char *AsciiStr_get(const AsciiStr *str, size_t i) {
    if (i < str->len)
        return str->ptr + i;

    out_of_bounds();
}

AsciiStr AsciiStr_substr(AsciiStr *str, size_t start, size_t end) {
    if (start >= str->len || end > str->len)
        out_of_bounds();

    if (start >= end) {
        AsciiStr substr = {};
        return substr;
    }

    AsciiStr substr = {
        .ptr = AsciiStr_get(str, start),
        .len = end - start,
    };

    return substr;
}

// AsciiString getters:

char *AsciiString_get(const AsciiString *str, size_t i) {
    if (i < str->len)
        return str->ptr + i;

    out_of_bounds();
}

AsciiStr AsciiString_asstr(AsciiString *str) {
    AsciiStr s = {
        .ptr = str->ptr,
        .len = str->len,
    };

    return s;
}

AsciiStr AsciiString_substr(AsciiString *str, size_t start, size_t end) {
    if (start >= str->len || end > str->len)
        out_of_bounds();

    if (start >= end) {
        AsciiStr substr = {};
        return substr;
    }

    AsciiStr substr = {
        .ptr = AsciiString_get(str, start),
        .len = end - start,
    };

    return substr;
}

// AsciiString setters:

void AsciiString_push(AsciiString *str, char c) {
    VoidVector_ensure_capacity((VoidVector *)str, sizeof(char), 1);

    str->ptr[str->len++] = c;
}

void AsciiString_extend_from(AsciiString *str, AsciiStr *src) {
    VoidVector_extend_from((VoidVector *)str, sizeof(char), (VoidArray *)src);
}

size_t AsciiString_reserve(AsciiString *str, size_t additional) {
    return VoidVector_reserve((VoidVector *)str, sizeof(char), additional);
}

// AsciiString destructors:

void AsciiString_free(AsciiString *str) { VoidVector_free((VoidVector *)str); }

// AsciiStringVector:

AsciiString *AsciiStringVector_get(const AsciiStringVector *v, size_t i) {
    if (i < v->len)
        return v->ptr + i;

    out_of_bounds();
}

void AsciiStringVector_push(AsciiStringVector *v, AsciiString *str) {
    VoidVector_ensure_capacity((VoidVector *)v, sizeof(AsciiString), 1);

    v->ptr[v->len++] = *str;
}

void AsciiStringVector_free(AsciiStringVector *v) {
    for (size_t i = 0; i < v->len; i++) {
        AsciiString_free(AsciiStringVector_get(v, i));
    }

    VoidVector_free((VoidVector *)v);
}
