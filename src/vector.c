#include "vector.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>
//
// size_t vector_reserve(size_t element_size, void **ptr, size_t *len, size_t *cap,
//                       size_t additional) {
//     if (additional == 0)
//         return cap;
//
//     size_t required_capacity = cap + additional;
//     void *new_ptr;
//
//     if ((new_ptr = malloc(required_capacity * element_size)) == NULL)
//         malloc_error();
//
//     memcpy(new_ptr, ptr, len * element_size);
//     free(ptr);
//     ptr = new_ptr;
//     cap = required_capacity;
//
//     return cap;
// }
//
// void *vector_push(size_t element_size, void **ptr, size_t *len, size_t *cap) {
//     vector_ensure_capacity(element_size, ptr, len, cap);
//
//     return ptr 
// }
//
// size_t vector_ensure_capacity(size_t element_size, void *ptr, size_t len,
//                               size_t cap, size_t additional) {
//     if (len < cap)
//         return 0;
//
//     return vector_reserve(element_size, ptr, len, cap, additional);
// }
