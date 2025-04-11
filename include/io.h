#ifndef IO_H
#define IO_H

#include "ascii_string.h"
#include <stdio.h>

ssize_t io_getline(AsciiString *str, FILE *restrict stream);

#endif // !IO_H
