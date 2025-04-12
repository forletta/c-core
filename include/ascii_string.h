#ifndef ASCII_STRING_H
#define ASCII_STRING_H

#include <stddef.h>

typedef struct {
    char *ptr;
    size_t len;
} AsciiStr;

typedef struct {
    char *ptr;
    size_t len;
    size_t cap;
} AsciiString;

// AsciiStr constructors:
AsciiStr AsciiStr_copy(AsciiStr *str);
AsciiStr AsciiStr_copy_from_cstr(char *str);
AsciiStr AsciiStr_take_from_cstr(char *str);

// AsciiStr getters:
char *AsciiStr_get(AsciiStr *str, size_t i);
AsciiStr AsciiStr_substr(AsciiStr *str, size_t start, size_t end);

// AsciiString getters:
char *AsciiString_get(AsciiString *str, size_t i);
AsciiStr AsciiString_substr(AsciiString *str, size_t start, size_t end);

// AsciiString setters:
size_t AsciiString_reserve(AsciiString *str, size_t additional);
void AsciiString_push(AsciiString *str, char c);
void AsciiString_extend_from(AsciiString *str, AsciiStr *src);

// AsciiString destructors:
void AsciiString_free(AsciiString *str);

#endif // !ASCII_STRING_H
