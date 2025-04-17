// #ifndef ASCII_STRING_H
// #define ASCII_STRING_H
//
// #include <stddef.h>
//
// typedef struct {
//     char *ptr;
//     size_t len;
// } AsciiStr;
//
// typedef struct {
//     char *ptr;
//     size_t len;
//     size_t cap;
// } AsciiString;
//
// typedef struct {
//     AsciiString *ptr;
//     size_t len;
//     size_t cap;
// } AsciiStringVector;
//
// // AsciiStr constructors:
// AsciiStr AsciiStr_copy(AsciiStr *str);
// AsciiStr AsciiStr_copy_from_cstr(char *cstr);
// AsciiStr AsciiStr_take_from_cstr(char *cstr);
//
// // AsciiStr getters:
// char *AsciiStr_get(const AsciiStr *str, size_t i);
// AsciiStr AsciiStr_substr(const AsciiStr *str, size_t start, size_t end);
//
// // AsciiStr constructors:
// AsciiString AsciiString_copy(AsciiString *str);
// AsciiString AsciiString_copy_from_str(AsciiStr *str);
// AsciiString AsciiString_take_from_str(AsciiStr str);
// AsciiString AsciiString_copy_from_cstr(char *cstr);
// AsciiString AsciiString_take_from_cstr(char *cstr);
//
// // AsciiString getters:
// char *AsciiString_get(const AsciiString *string, size_t i);
// AsciiStr AsciiString_asstr(const AsciiString *string);
// AsciiStr AsciiString_substr(const AsciiString *string, size_t start, size_t end);
//
// // AsciiString setters:
// // size_t AsciiString_reserve(AsciiString *str, size_t additional);
// void AsciiString_push(AsciiString *str, char c);
// void AsciiString_extend_from(AsciiString *str, AsciiStr *src);
//
// // AsciiString destructors:
// void AsciiString_free(AsciiString *string);
//
// // AsciiStringVector:
// AsciiString *AsciiStringVector_get(const AsciiStringVector *v, size_t i);
// void AsciiStringVector_push(AsciiStringVector *v, AsciiString *str);
// void AsciiStringVector_free(AsciiStringVector *v);
//
// #endif // !ASCII_STRING_H
