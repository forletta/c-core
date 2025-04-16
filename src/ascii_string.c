#include "ascii_string.h"
#include "array.h"
#include "void_array.h"
#include "void_vector.h"
// #include "c_core_error.h"
// #include "void_array.h"
// #include "void_vector.h"
#include <stdlib.h>
#include <string.h>

// AsciiStr constructors:

AsciiStr AsciiStr_copy(AsciiStr *str) {
    AsciiStr new = {
        .ptr = array_copy(sizeof(char), str->ptr, str->len),
        .len = str->len,
    };

    return new;
}

AsciiStr AsciiStr_copy_from_cstr(char *cstr) {
    size_t len = strlen(cstr);
    AsciiStr new = {
        .ptr = array_copy(sizeof(char), cstr, len),
        .len = len,
    };

    return new;
}

AsciiStr AsciiStr_take_from_cstr(char *cstr) {
    AsciiStr str = {
        .ptr = cstr,
        .len = strlen(cstr),
    };

    return str;
}

// AsciiStr getters:

char *AsciiStr_get(const AsciiStr *str, size_t i) {
    return array_get(sizeof(char), str->ptr, str->len, i);
}

AsciiStr AsciiStr_substr(const AsciiStr *str, size_t start, size_t end) {
    AsciiStr substr;

    if ((substr.ptr =
             array_get_slice(sizeof(char), str->ptr, str->len, start, end))) {
        substr.len = 0;
    } else {
        substr.len = end - start;
    }

    return substr;
}

// AsciiStr constructors:

AsciiString AsciiString_copy_from_str(AsciiStr *str) {
    AsciiStr copy = AsciiStr_copy(str);

    return AsciiString_take_from_str(copy);
}

AsciiString AsciiString_take_from_str(AsciiStr str) {
    AsciiString string = {
        .ptr = str.ptr,
        .len = str.len,
        .cap = str.len,
    };

    return string;
}

AsciiString AsciiString_copy_from_cstr(char *cstr) {
    return AsciiString_take_from_str(AsciiStr_copy_from_cstr(cstr));
}

AsciiString AsciiString_take_from_cstr(char *cstr) {
    return AsciiString_take_from_str(AsciiStr_take_from_cstr(cstr));
}

// AsciiString getters:

char *AsciiString_get(const AsciiString *string, size_t i) {
    AsciiStr str = AsciiString_asstr(string);
    return AsciiStr_get(&str, i);
}

AsciiStr AsciiString_asstr(const AsciiString *string) {
    AsciiStr str = {
        .ptr = string->ptr,
        .len = string->len,
    };

    return str;
}

AsciiStr AsciiString_substr(const AsciiString *string, size_t start,
                            size_t end) {
    AsciiStr str = AsciiString_asstr(string);
    return AsciiStr_substr(&str, start, end);
}

VoidVector AsciiString_as_void_vector(AsciiString *string) {
    VoidVector v = {
        .ptr = (void **)&string->ptr,
        .len = &string->len,
        .cap = &string->cap,
        .element_size = sizeof(char),
    };

    return v;
}

// AsciiString setters:

void AsciiString_push(AsciiString *string, char c) {
    VoidVector v = AsciiString_as_void_vector(string);

    char *target = VoidVector_push(&v);
    *target = c;
}

void AsciiString_extend_from(AsciiString *string, AsciiStr *str) {
    VoidVector v = AsciiString_as_void_vector(string);
    VoidArray arr = {
        .ptr = str->ptr,
        .len = str->len,
    };

    VoidVector_extend_from(&v, &arr);
}

void AsciiString_free(AsciiString *string) {
    VoidVector v = AsciiString_as_void_vector(string);
    VoidVector_free(&v);
}

// AsciiStringVector:

AsciiString *AsciiStringVector_get(const AsciiStringVector *v, size_t i) {
    return array_get(sizeof(AsciiString), v->ptr, v->len, i);
}

VoidVector AsciiStringVector_as_void_vector(AsciiStringVector *v) {
    VoidVector void_v = {
        .ptr = (void **)&v->ptr,
        .len = &v->len,
        .cap = &v->cap,
        .element_size = sizeof(AsciiString),
    };

    return void_v;
}

void AsciiStringVector_push(AsciiStringVector *v, AsciiString *str) {
    VoidVector void_v = AsciiStringVector_as_void_vector(v);

    *(AsciiString *)VoidVector_push(&void_v) = *str;
}

void AsciiStringVector_free(AsciiStringVector *v) {
    for (size_t i = 0; i < v->len; i++) {
        AsciiString_free(AsciiStringVector_get(v, i));
    }

    VoidVector void_v = AsciiStringVector_as_void_vector(v);
    VoidVector_free(&void_v);
}

// // AsciiString constructors:
// AsciiString AsciiString_copy(AsciiString *str) {
//     VoidVector void_vector = VoidVector_copy((VoidVector *)str,
//     sizeof(char));
//
//     return *(AsciiString *)&void_vector;
// }
//
// AsciiString AsciiString_copy_from_str(AsciiStr *str) {
//     return AsciiString_take_from_str(AsciiStr_copy(str));
// }
//
// AsciiString AsciiString_take_from_str(AsciiStr str) {
//     AsciiString string = {
//         .ptr = str.ptr,
//         .len = str.len,
//         .cap = str.len,
//     };
//
//     return string;
// }
//
// AsciiString AsciiString_copy_from_cstr(char *str) {
//     return AsciiString_take_from_str(AsciiStr_copy_from_cstr(str));
// }
//
// AsciiString AsciiString_take_from_cstr(char *str) {
//     return AsciiString_take_from_str(AsciiStr_take_from_cstr(str));
// }
//
// // AsciiString getters:
//
// char *AsciiString_get(const AsciiString *str, size_t i) {
//     if (i < str->len)
//         return str->ptr + i;
//
//     out_of_bounds();
// }
//
// AsciiStr AsciiString_asstr(AsciiString *str) {
//     AsciiStr s = {
//         .ptr = str->ptr,
//         .len = str->len,
//     };
//
//     return s;
// }
//
// AsciiStr AsciiString_substr(AsciiString *str, size_t start, size_t end) {
//     if (start >= str->len || end > str->len)
//         out_of_bounds();
//
//     if (start >= end) {
//         AsciiStr substr = {};
//         return substr;
//     }
//
//     AsciiStr substr = {
//         .ptr = AsciiString_get(str, start),
//         .len = end - start,
//     };
//
//     return substr;
// }
//
// // AsciiString setters:
//
// void AsciiString_push(AsciiString *str, char c) {
//     VoidVector_ensure_capacity((VoidVector *)str, sizeof(char), 1);
//
//     str->ptr[str->len++] = c;
// }
//
// void AsciiString_extend_from(AsciiString *str, AsciiStr *src) {
//     VoidVector_extend_from((VoidVector *)str, sizeof(char), (VoidArray
//     *)src);
// }
//
// size_t AsciiString_reserve(AsciiString *str, size_t additional) {
//     return VoidVector_reserve((VoidVector *)str, sizeof(char), additional);
// }
//
// // AsciiString destructors:
//
// void AsciiString_free(AsciiString *str) { VoidVector_free((VoidVector *)str);
// }
//
// // AsciiStringVector:
//
// AsciiString *AsciiStringVector_get(const AsciiStringVector *v, size_t i) {
//     if (i < v->len)
//         return v->ptr + i;
//
//     out_of_bounds();
// }
//
// void AsciiStringVector_push(AsciiStringVector *v, AsciiString *str) {
//     VoidVector_ensure_capacity((VoidVector *)v, sizeof(AsciiString), 1);
//
//     v->ptr[v->len++] = *str;
// }
//
// void AsciiStringVector_free(AsciiStringVector *v) {
//     for (size_t i = 0; i < v->len; i++) {
//         AsciiString_free(AsciiStringVector_get(v, i));
//     }
//
//     VoidVector_free((VoidVector *)v);
// }
