#include "array.h"
#include "c_core_error.h"
#include <stdlib.h>
#include <string.h>

// Constructors:

void *array_copy(size_t element_size, void *ptr, size_t len) {
    void *new = array_alloc(element_size, len);

    memcpy(new, ptr, len * element_size);

    return new;
}

void *array_alloc(size_t element_size, size_t len) {
    void *ptr;

    if ((ptr = malloc(len * element_size)) == NULL)
        malloc_error();

    return ptr;
}

// Getters:

void *array_get(size_t element_size, void *ptr, size_t len, size_t i) {
    if (i >= len)
        out_of_bounds();

    return ptr + (i * element_size);
}

void *array_get_slice(size_t element_size, void *ptr, size_t len, size_t start, size_t end) {
    if (start >= len || end > len)
        out_of_bounds();

    if (start > end)
        return NULL;

    return array_get(element_size, ptr, len, start);
}
