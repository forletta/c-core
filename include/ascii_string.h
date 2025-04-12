#ifndef ASCII_STRING_H
#define ASCII_STRING_H

#include <stddef.h>

typedef struct {
    char *const ptr;
    const size_t len;
} AsciiStr;

typedef struct {
    char *ptr;
    size_t len;
    size_t cap;
} AsciiString;

// AsciiStr constructors:
AsciiStr AsciiStr_copy(const AsciiStr *str);
AsciiStr AsciiStr_copy_from_cstr(const char *str);
AsciiStr AsciiStr_take_from_cstr(char *const str);

// AsciiStr getters:
char *const AsciiStr_get(const AsciiStr *str, size_t i);
AsciiStr AsciiStr_substr(const AsciiStr *str, size_t start, size_t end);

// AsciiString getters:
char *const AsciiString_get(const AsciiString *str, size_t i);
AsciiStr AsciiString_substr(const AsciiString *str, size_t start, size_t end);

// AsciiString setters:
size_t AsciiString_reserve(AsciiString *str, size_t additional);
void AsciiString_push(AsciiString *str, char c);
void AsciiString_extend_from(AsciiString *str, const AsciiStr *src);

// AsciiString destructors:
void AsciiString_free(AsciiString *str);

#endif // !ASCII_STRING_H
