#ifndef ASCII_STRING_H
#define ASCII_STRING_H

#include <stddef.h>

typedef struct {
    char *str;
    size_t len;
} AsciiStr;

typedef struct {
    AsciiStr str;
    size_t cap;
} AsciiString;

AsciiStr AsciiStr_copy(AsciiStr *str);
AsciiStr AsciiStr_copy_from_cstr(char *str);

char *AsciiStr_get(AsciiStr *str, size_t i);

size_t AsciiString_reserve(AsciiString *str, size_t additional);

char *AsciiString_get(AsciiString *str, size_t i);
void AsciiString_push(AsciiString *str, char c);
AsciiStr AsciiString_extend_from(AsciiString *str, AsciiStr *src);

#endif // !ASCII_STRING_H
