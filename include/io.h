#ifndef IO_H
#define IO_H

#include "char_array.h"
#include <stdio.h>

ssize_t io_getline(charArray *str, FILE *restrict stream);

#endif // !IO_H
