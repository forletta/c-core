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

AsciiStr AsciiStr_copy(const AsciiStr *str);
AsciiStr AsciiStr_copy_from_cstr(const char *str);
const AsciiStr AsciiStr_take_from_cstr(const char *str);

const char *AsciiStr_get(const AsciiStr *str, size_t i);

size_t AsciiString_reserve(AsciiString *str, size_t additional);

const char *AsciiString_get(const AsciiString *str, size_t i);
void AsciiString_push(AsciiString *str, char c);
void AsciiString_extend_from(AsciiString *str, const AsciiStr *src);

void AsciiStr_free(AsciiStr *str);
void AsciiString_free(AsciiString *str);

#endif // !ASCII_STRING_H
