// #include "uint8_vector.h"
// #include "uint8_array.h"
// #include "void_array.h"
// #include "void_vector.h"
// #include <stdlib.h>
// #include <string.h>
//
// size_t Uint8Vector_reserve(Uint8Vector *v, size_t additional) {
//     return VoidVector_reserve((VoidVector *)v, sizeof(uint8_t), additional);
// }
//
// uint8_t *const Uint8Vector_get(const Uint8Vector *v, size_t i) {
//     return Uint8Array_get(&v->arr, i);
// }
//
// void Uint8Vector_push(Uint8Vector *v, uint8_t value) {
//     VoidVector_ensure_capacity((VoidVector *)v, sizeof(uint8_t), 1);
//
//     v->arr.arr[v->arr.len++] = value;
// }
//
// void Uint8Vector_extend_from(Uint8Vector *v, const Uint8Array *src) {
//     VoidVector_extend_from((VoidVector *)v, sizeof(uint8_t),
//                            (const VoidArray *)src);
// }
//
// void Uint8Vector_free(Uint8Vector *v) { VoidVector_free((VoidVector *)v); }
