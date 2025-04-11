#include "io.h"
#include "ascii_string.h"
#include <stddef.h>

ssize_t io_getline(AsciiString *str, FILE *restrict stream) {
    ssize_t bytes_read = getline(&str->str.str, &str->cap, stream);

    // This is zeroed in the next line if negative
    str->str.len = bytes_read;

    if (bytes_read < 0)
        AsciiString_free(str);

    return bytes_read;
}
