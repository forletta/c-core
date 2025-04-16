#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

// Constructors:

void *array_copy(size_t element_size, void *ptr, size_t len);
void *array_alloc(size_t element_size, size_t len);

// Getters:

void *array_get(size_t element_size, void *ptr, size_t len, size_t i);
void *array_get_slice(size_t element_size, void *ptr, size_t len, size_t start, size_t end);

#endif // !ARRAY_H
